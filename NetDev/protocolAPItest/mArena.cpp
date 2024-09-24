#include <iostream>
#include <string>
#include <google/protobuf/arena.h>

using namespace google::protobuf;


class mClass {
public:
    mClass(): num(0) {};
    mClass(int n): num(n) {};
    int getNumber() {return num;}
    void setNumber(int n) {num = n;}

private:
    int num;
};

class mString {
public:
    mString(): ptr(nullptr) {}
    mString(std::string& str) {
        ptr = new std::string(str);
    }

    mString(const mString& x) {
        if (ptr != nullptr) delete ptr;
        ptr = new std::string(x.print());
    }

    const std::string& print() const {
        return *ptr;
    }

    ~mString() {delete ptr;}

private:
    std::string *ptr;
};  


int main(int argc, char* argv[]) {
    int test = 666;
    google::protobuf::Arena arena;
    std::cout << "Initialization Allocated Space: " << arena.SpaceAllocated()
              << " Used Space: " << arena.SpaceUsed() << std::endl;
    
    std::string str0 = "Arena allocator:";
    std::string str1 = "1) allocation relaces ordinary (heap-based) allocation with new/delete";
    std::string str2 = "2) improves performance by aggregating allocations into larger blocks";
    std::string str3 = "3) freeing allocations all at once";

    mClass* c1 = google::protobuf::Arena::Create<mClass>(&arena, test);
    std::cout << "Allocated add mClass c1 (666): " << arena.SpaceAllocated()
              << " Used Space: " << arena.SpaceUsed() << std::endl;
    
    mString* s0 = google::protobuf::Arena::Create<mString>(&arena, str0);
    std::cout << "Allocated add mString str: " << str0 
              << " " << arena.SpaceAllocated()
              << " Used Space: " << arena.SpaceUsed() << std::endl;
    
    mString* s1 = google::protobuf::Arena::Create<mString>(&arena, str1);
    std::cout << "Allocated add mString str: " << str1
              << " " << arena.SpaceAllocated()
              << " Used Space: " << arena.SpaceUsed() << std::endl;

    mString* s2 = google::protobuf::Arena::Create<mString>(&arena, str2);
    std::cout << "Allocated add mString str: " << str2
              << " " << arena.SpaceAllocated()
              << " Used Space: " << arena.SpaceUsed() << std::endl;

    mString* s3 = google::protobuf::Arena::Create<mString>(&arena, str3);
    std::cout << "Allocated add mString str: " << str3
              << " " << arena.SpaceAllocated()
              << " Used Space: " << arena.SpaceUsed() << std::endl;

    std::cout << "c1->getNumber(): " << c1->getNumber() << std::endl;
    // std::cout << s0->print() << std::endl;
    // std::cout << s1->print() << std::endl;
    // std::cout << s2->print() << std::endl;
    // std::cout << s3->print() << std::endl;

    arena.Reset();
    std::cout << "Allocated after reset(): " << arena.SpaceAllocated()
              << " Used Space: " << arena.SpaceUsed() << std::endl;

    return 0;
}
