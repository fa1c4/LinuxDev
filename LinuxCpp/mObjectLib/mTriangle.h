#ifndef MRECTANGLE_H
#define MRECTANGLE_H

class mTriangle {
public:
    mTriangle(double length, double width);
    mTriangle();
    
    double getArea() const;
    double getLength() const;
    double getWidth() const;
    void setLength(double length);
    void setWidth(double width);
    void setBaseHeight(double length, double width);

private:
    double length;
    double width;
};

#endif // MRECTANGLE_H
