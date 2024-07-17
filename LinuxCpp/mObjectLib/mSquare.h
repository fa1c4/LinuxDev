#ifndef MSQUARE_H
#define MSQUARE_H

class mSquare {
public:
    mSquare(double side);
    mSquare();
    double getArea() const;
    double getSide() const;
    void setSide(double side);

private:
    double side;
};

#endif // MSQUARE_H