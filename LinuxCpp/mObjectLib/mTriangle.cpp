#include "mTriangle.h"

mTriangle::mTriangle(double length, double width) : length(length), width(width) {}

mTriangle::mTriangle() {}

double mTriangle::getArea() const {
    return length * width;
}

double mTriangle::getLength() const {
    return length;
}

double mTriangle::getWidth() const {
    return width;
}

void mTriangle::setLength(double length) {
    this->length = length;
}

void mTriangle::setWidth(double width) {
    this->width = width;
}

void mTriangle::setBaseHeight(double length, double width) {
    this->length = length;
    this->width = width;
}