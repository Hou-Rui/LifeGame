#ifndef CELL_HPP
#define CELL_HPP

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT
    int  _hp;
    bool _food;
public:
    explicit Cell(QObject *parent = 0, int hp = 100);
    static Cell *newFood(QObject *parent);

    int  hp() { return _hp; }
    void incHp(int x);
    void decHp(int x);

    bool isFood() { return _food; }

/*
signals:
    void died();
    void born();
    void eaten();
    void willCopy();
*/
};

#endif // CELL_HPP
