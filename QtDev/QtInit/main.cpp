#include <iostream>
#include "qtcircle.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    // test circle set radium and caculation
    QtCircle testcircle(1);
//    testcircle.setRadium(1);
    cout << "Circle perimeter is: " << testcircle.getPerimeter() << "m" << endl;
    cout << "Circle Area is: " << testcircle.getArea() << "m^2" << endl;

    int radi = 0;
    cout << "input your radium value: " << endl;
    cin >> radi;
    testcircle.setRadium(radi);
    cout << "Circle perimeter is: " << testcircle.getPerimeter() << "m" << endl;
    cout << "Circle Area is: " << testcircle.getArea() << "m^2" << endl;

    return 0;
}
