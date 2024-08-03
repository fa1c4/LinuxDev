#include <iostream>
#include <thread>
#include <future>
#include <exception>


int mFunction(int tid) {
    int totLoop = 0;
    for (int j = 0; j <= 100000; ++j) {
        if (j % 50000 == 0)
            std::cout << "Thread Numm: " << tid << " at loop number " << j << std::endl;
    }
    return totLoop;
}

// async implementation
int main() {
    int ret = 0;
    std::future<int> mTH[5];
    for (int i = 0; i < 5; ++i) {
        mTH[i] = std::async(mFunction, i);
    }
    for (int i = 0; i < 5; ++i) {
        ret = mTH[i].get();
    }
    return ret;
}

/* thread implementation
int main() {
    int ret = 0;
    std::thread mTH[5];
    for (int i = 0; i < 5; ++i) {
        mTH[i] = std::thread(mFunction, i);
    }
    for (int i = 0; i < 5; ++i) {
        mTH[i].join();
    }
    return ret;
}
*/
