#include "worldframe.hpp"

WorldFrame::WorldFrame(QWidget *parent)
    : QFrame(parent)
{
    // 初始化
    setFixedSize(QSize(PIX_HEIGHT, PIX_WIDTH));
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    memset(cells, (int)NULL, sizeof cells);
    time = 0;
}

QRect WorldFrame::getRect(int x, int y)
{
    return QRect(x * (PIX_WIDTH / GRID_WIDTH), y * (PIX_HEIGHT / GRID_HEIGHT),
                 PIX_WIDTH / GRID_WIDTH, PIX_HEIGHT / GRID_HEIGHT);
}

void WorldFrame::paintLife(int x, int y)
{
    QPainter p(this);
    p.fillRect(getRect(x, y), QColor(0, 255, 0));
}

void WorldFrame::paintEmpty(int x, int y)
{
    QPainter p(this);
    p.fillRect(getRect(x, y), QColor(0, 0, 0));
}

void WorldFrame::paintFood(int x, int y)
{
    QPainter p(this);
    p.fillRect(getRect(x, y), QColor(255, 200, 100));
}

void WorldFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    int fdcnt = 0, clcnt = 0;
    for (int i = 0; i < GRID_HEIGHT; i++)
    for (int j = 0; j < GRID_WIDTH; j++)
    {
        Cell *c = cells[i][j];
        if (c == NULL) paintEmpty(i, j);
        else if (c->isFood())
        {
            paintFood(i, j);
            fdcnt++;
        }
        else
        {
            paintLife(i, j);
            clcnt++;
        }
    }
    emit cellCountChanged(clcnt);
    emit foodCountChanged(fdcnt);
}

void WorldFrame::init()
{
    int cellCount = 0, foodCount = 0;
    // 放细胞
    for (int i = 0; i < 50; i++)
    {
        int nx = qrand() % GRID_WIDTH, ny = qrand() % GRID_HEIGHT;
        if (cells[nx][ny]) continue;
        cells[nx][ny] = new Cell(parent());
        cellCount++;
        emit cellCountChanged(cellCount);
    }

    // 放食物
    for (int i = 0; i < 200; i++)
    {
        int nx = qrand() % GRID_WIDTH, ny = qrand() % GRID_HEIGHT;
        if (cells[nx][ny]) continue;
        cells[nx][ny] = Cell::newFood(parent());
        foodCount++;
        emit foodCountChanged(foodCount);
    }

    update();
}

void WorldFrame::start()
{
    timer = new QTimer();
    timer->setInterval(500); // 0.5秒
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start();
}

void WorldFrame::pause()
{
    timer->stop();
}

bool WorldFrame::isValid(int x, int y)
{
    return x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT;
}

static const int dx[] = {-1, 0, 0, 1, -1, -1, 1, 1};
static const int dy[] = {0, -1, 1, 0, -1, 1, -1, 1};

void WorldFrame::onTimeout()
{
    // 更新时间
    time++;
    emit timeChanged(time);

    // 生成随机序列
    std::default_random_engine eng;
    std::array<int, GRID_WIDTH> qa;
    std::array<int, GRID_HEIGHT> qb;

    std::iota(qa.begin(), qa.end(), 0);
    std::iota(qb.begin(), qb.end(), 0);
    std::shuffle(qa.begin(), qa.end(), eng);
    std::shuffle(qb.begin(), qb.end(), eng);

    for (int i : qa)
    for (int j : qb)
    {
        Cell *&c = cells[i][j];
        if (!c) continue;
        if (c->isFood())
        {
            if (c->hp() < 0) delete cells[i][j], cells[i][j] = NULL;
            continue;
        }
        c->decHp(1);

        bool wander = true;
        std::array<int, 8> qk;
        std::iota(qk.begin(), qk.end(), 0);
        std::shuffle(qk.begin(), qk.end(), eng);
        for (int k : qk)
        {
            if (!isValid(i + dx[k], j + dy[k])) continue;
            Cell *&d = cells[i + dx[k]][j + dy[k]];
            if (d && d->isFood())
            {
                c->incHp(30);
                d->decHp(30);
                wander = false;
                break;
            }
        }

        if (c->hp() > 150)
        {
            int rd = qrand() % 8;
            if (!isValid(i + dx[rd], j + dy[rd])) continue;
            c->decHp(75);
            cells[i + dx[rd]][j + dy[rd]] = new Cell(this, 75);
        }

        if (wander)
        {
            int rd = qrand() % 8;
            if (!isValid(i + dx[rd], j + dy[rd])) continue;
            std::swap(c, cells[i + dx[rd]][j + dy[rd]]);
        }
    }

    update();
}
