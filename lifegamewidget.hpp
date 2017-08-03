#ifndef LIFEGAMEWIDGET_HPP
#define LIFEGAMEWIDGET_HPP

#include "worldframe.hpp"
#include <QtWidgets>

class LifeGameWidget : public QWidget
{
    Q_OBJECT
    WorldFrame  *world;
    QPushButton *initButton;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QHBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;
    QLabel      *lifeLabel;
    QLabel      *foodLabel;
    QLabel      *timeLabel;

public:
    explicit LifeGameWidget(QWidget *parent = 0);
    ~LifeGameWidget();
};

#endif // LIFEGAMEWIDGET_HPP
