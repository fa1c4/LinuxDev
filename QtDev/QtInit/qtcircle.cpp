#include "qtcircle.h"

QtCircle::QtCircle() : radium(0)
{
//    radium = 0;
}

QtCircle::QtCircle(int r) : radium(r)
{
//    radium = 0;
}


void QtCircle::setRadium(int r) {
    radium = r;
}

float QtCircle::getArea() {
    return PI * radium * radium;
}

float QtCircle::getPerimeter() {
    return PI * 2 * radium;
}
