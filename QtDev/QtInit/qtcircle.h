#ifndef QTCIRCLE_H
#define QTCIRCLE_H


class QtCircle
{
public:
    QtCircle();
    QtCircle(int r);
    void setRadium(int r);
    float getArea();
    float getPerimeter();

private:
    int radium;
    float PI = 3.14159;
};

#endif // QTCIRCLE_H
