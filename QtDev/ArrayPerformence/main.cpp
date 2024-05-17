#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <array>
#include <vector>

using namespace std;

int main()
{
    int  INTS[1000000];
    std::array<int, 1000000> ARRS;
    std::vector<int> VECS;

    srand(time(NULL));

    // int array
    chrono::high_resolution_clock::time_point timeStart = chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        INTS[i] = rand() % 100 + 1;
    }

    chrono::high_resolution_clock::time_point timeEnd = chrono::high_resolution_clock::now();
    chrono::milliseconds execTime = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);
    cout << "int array executing time is: " << execTime.count() << "ms" << endl;

    // std::array
    timeStart = chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        ARRS[i] = rand() % 100 + 1;
    }

    timeEnd = chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);
    cout << "std array executing time is: " << execTime.count() << "ms" << endl;

    // std::vector
    timeStart = chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        VECS.push_back(rand() % 100 + 1);
    }

    timeEnd = chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);
    cout << "std vector executing time is: " << execTime.count() << "ms" << endl;

    return 0;
}
