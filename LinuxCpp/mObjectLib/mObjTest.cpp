#include <iostream>
#include "mSquare.h"
#include "mTriangle.h"

using namespace std;


int main() {
    mSquare mSqre;
    mSqre.setSide(42.10101);

    mTriangle mTri;
    mTri.setBaseHeight(2.5, 3.99);

    cout << "Test Square area is: " << mSqre.getArea() << endl;
    cout << "Test Triangle area is: " << mTri.getArea() << endl;

    return 0;
}
