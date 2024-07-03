#include <string>
#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef chrono::milliseconds millsecs;

class mData {
private:
    std::string* pData;
    int id;

public:
    mData (const std::string& inStr, int id) {
        pData = new std::string(inStr);
        id = id;
        // std::cout << "Class mData created " << id << " " << pData << " " << *pData << std::endl;
    }

    // copying constructor
    mData (const mData& inObj) {
        pData = new std::string(*inObj.pData);
        id = inObj.id - 1;
        // std::cout << "Class mData copied " << id << " " << pData << " " << *pData << std::endl;
    }

    // moving constructor
    // mData (mData& inObj) {
    //     pData = new std::string(*inObj.pData);
    //     id = inObj.id - 1;
    //     // std::cout << "Class mData copied " << id << " " << pData << " " << *pData << std::endl;
    // }

    // moving constructor
    // mData (mData&& inObj) {
    //     pData = inObj.pData;
    //     id = inObj.id;
    //     inObj.pData = nullptr;
    //     // std::cout << "Class mData moved " << id << " " << pData << " " << *pData << std::endl;
    // }

    ~mData() {
        delete pData;
    }
};


int main() {
    mData mObject = mData("This is my fantasy data class", 999);
    mData mCopy = mData(mObject);

    std::vector<mData> mVecs;
    // mVecs push_back will copy the object
    // mVecs.push_back(mData("test for push_back operation copy", 233));

    // test for push_back with different constructors: copy and move
    // test for move push back
    // Clock::time_point tStart = Clock::now();
    // for (int i = 0; i < 1000000; ++i) {
    //     mVecs.push_back(mData("test for push_back operation copy", i));
    // }
    // Clock::time_point tEnd = Clock::now();
    // millsecs execTime = chrono::duration_cast<millsecs>(tEnd - tStart);
    // cout << "moving constructor time used for push back 1M objects: " << execTime.count() << "ms" << endl;
    // 540 ms

    // test for copy push back
    Clock::time_point tStart = Clock::now();
    for (int i = 0; i < 1000000; ++i) {
        mVecs.push_back(mData("test for push_back operation copy", i));
    }
    Clock::time_point tEnd = Clock::now();
    millsecs execTime = chrono::duration_cast<millsecs>(tEnd - tStart);
    cout << "copying constructor time used for push back 1M objects: " << execTime.count() << "ms" << endl;
    // 1195 ms

    return 0;
}
