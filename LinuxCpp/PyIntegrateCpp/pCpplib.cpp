#include <iostream>
#include <boost/python.hpp>
using namespace boost::python;


char const* mMessage() {
    return "Message from fa1c4";
}

int const mAdd(int a, int b) {
    return a + b;
}

class mClass {
public:
    mClass(std::string str): name(str), mNumber(0.0) {}
    std::string name;
    double getNumber() const {return mNumber;}
    void setNumber(double n) {mNumber = n;}

private:
    double mNumber;
};

BOOST_PYTHON_MODULE(pCpplib) {
    def("mMessage", mMessage);
    def("mAdd", mAdd);
    class_<mClass>("mClass", init<std::string>())
        .def_readwrite("name", &mClass::name)
        .def("Get", &mClass::getNumber)
        .def("Set", &mClass::setNumber);
}
