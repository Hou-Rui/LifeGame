#include "cell.hpp"

Cell::Cell(QObject *parent, int hp) : QObject(parent)
{
    // emit born();
    _hp = hp;
    _food = false;
}

Cell *Cell::newFood(QObject *parent)
{
    Cell *c = new Cell(parent);
    c->_food = true;
    c->_hp = 50;
    return c;
}

void Cell::incHp(int x)
{
    _hp += x;
    // if (_hp > 100)
    //    emit willCopy();
}


void Cell::decHp(int x)
{
    _hp -= x;
    if (_hp <= 0)
    {
        if (!_food)
        {
            // emit died();
            _food = true;
            _hp = 50;
        }
        // else emit eaten();
    }
}


