#include <iostream>
#include "nodebase.h"
// #include "nodelist.h"

using namespace std;


int main() {
    // NodeBase mObj1("Object 1");
    // NodeBase mObj2("Object 2");
    // mObj1.displayNodeBase();
    // mObj2.displayNodeBase();

    // link objects
    Node mObj1("Object 1");
    Node mObj2("Object 2");

    mObj1.setLink(&mObj2);
    mObj1.displayNode();
    mObj1.getLinkNode()->displayNode();

    return 0;
}
