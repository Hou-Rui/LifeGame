#ifndef WORLDFRAME_HPP
#define WORLDFRAME_HPP

#include "cell.hpp"
#include <QtWidgets>
#include <algorithm>
#include <array>
#include <random>
#include <ctime>

class WorldFrame : public QFrame
{
    Q_OBJECT
    static const int PIX_WIDTH = 500;
    static const int PIX_HEIGHT = 500;
    static const int GRID_WIDTH = 100;
    static const int GRID_HEIGHT = 100;

    Cell*   cells[GRID_WIDTH][GRID_HEIGHT];
    QTimer* timer;
    int     time;

    Cell* newCell   (int x, int y);
    QRect getRect   (int x, int y);
    void  paintLife (int x, int y);
    void  paintFood (int x, int y);
    void  paintEmpty(int x, int y);
    bool  isValid   (int x, int y);

public:
    explicit WorldFrame(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;

signals:
    void cellCountChanged(int newValue);
    void foodCountChanged(int newValue);
    void timeChanged     (int newValue);

public slots:
    void init();
    void start();
    void pause();
    void onTimeout();
};

#endif // WORLDFRAME_HPP
