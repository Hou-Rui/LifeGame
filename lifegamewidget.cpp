#include "lifegamewidget.hpp"

LifeGameWidget::LifeGameWidget(QWidget *parent)
    : QWidget(parent)
{
    // 自己的初始化
    setWindowTitle("细胞模拟器");
    setMinimumSize(QSize(500, 500));

    mainLayout  = new QHBoxLayout(this);
    rightLayout = new QVBoxLayout;

    world       = new WorldFrame (this);
    initButton  = new QPushButton(this);
    startButton = new QPushButton(this);
    pauseButton = new QPushButton(this);

    // 初始化lifeLabel和foodLabel
    lifeLabel = new QLabel("生命总数：0");
    foodLabel = new QLabel("食物总数：0");
    timeLabel = new QLabel("时间：0");
    connect(world, &WorldFrame::cellCountChanged, [=](int x)
        { lifeLabel->setText(QString("生命总数：%1").arg(x)); });
    connect(world, &WorldFrame::foodCountChanged, [=](int x)
        { foodLabel->setText(QString("食物总数：%1").arg(x)); });
    connect(world, &WorldFrame::timeChanged, [=](int x)
        { timeLabel->setText(QString("时间：%1").arg(x)); });
    rightLayout->addWidget(lifeLabel);
    rightLayout->addWidget(foodLabel);
    rightLayout->addWidget(timeLabel);

    // 初始化initButton
    initButton->setText("初始化");
    rightLayout->addWidget(initButton);
    connect(initButton, SIGNAL(clicked()), world, SLOT(init()));

    // 初始化startButton
    startButton->setText("开始模拟");
    rightLayout->addWidget(startButton);
    connect(startButton, SIGNAL(clicked()), world, SLOT(start()));

    // 初始化pauseButton
    pauseButton->setText("停止模拟");
    rightLayout->addWidget(pauseButton);
    connect(pauseButton, SIGNAL(clicked()), world, SLOT(pause()));

    // 初始化mainLayout
    mainLayout->addWidget(world);
    mainLayout->addLayout(rightLayout);
}

LifeGameWidget::~LifeGameWidget()
{

}
