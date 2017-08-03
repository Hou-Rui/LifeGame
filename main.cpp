#include "lifegamewidget.hpp"
#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    qsrand(std::time(0));
    QApplication a(argc, argv);
    LifeGameWidget w;
    w.show();

    return a.exec();
}
