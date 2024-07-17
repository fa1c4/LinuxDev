#include "mSquare.h"

mSquare::mSquare(double side) : side(side) {}

mSquare::mSquare() {}

double mSquare::getArea() const {
    return side * side;
}

double mSquare::getSide() const {
    return side;
}

void mSquare::setSide(double side) {
    this->side = side;
}
