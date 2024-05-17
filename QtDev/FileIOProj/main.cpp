#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[])
{
    std::string line;
    if (argc >= 2) {
        ifstream mFilein(argv[1]);
        int cnt = 0;
        if (mFilein.is_open()) {
            cnt = 0;
            while (getline(mFilein, line)) {
                if (cnt % 1000 == 0)
                    std::cout << line << endl;
            }
            mFilein.close();
        }
    } else {
        std::cout << "usage: ./binary file_to_read" << endl;
    }

    return 0;
}
