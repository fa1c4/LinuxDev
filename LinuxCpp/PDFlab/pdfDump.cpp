#include <iostream>
#include <fstream>
#include <string.h>
#include <string>


#define BUFFER_SIZE 1024
using namespace std;

int main(int argc, char* argv[]) {
    int i = 0, j = 0;
    char inBuf[BUFFER_SIZE];
    char workBuf[BUFFER_SIZE];

    if (argc != 3) {
        cout << "Usage: pdfParser <inPDF file> <outText file>" << endl;
        exit(1);
    }

    ifstream inFile(argv[1], ios::in | ios::binary);
    if (!inFile.is_open()) {
        cout << "file open error: " << argv[1] << endl;
        exit(-1);
    }

    ofstream outFile(argv[2], ios::out);
    if (!outFile.is_open()) {
        cout << "file open error: " << argv[2] << endl;
        exit(-2);
    } 

    memset(workBuf, '\0', sizeof(workBuf));
    while (!inFile.eof()) {
        // read all content until eof
        memset(inBuf, '\0', sizeof(inBuf));
        inFile.read(reinterpret_cast<char*>(inBuf), sizeof(inBuf));

        for (i = 0; i < (int)sizeof(inBuf); ++i) {
            char mChar = inBuf[i];
            int mInt = int(mChar);

            if (mChar == 0x0A || j == BUFFER_SIZE) {
                // 0x0A is \n
                outFile.write(workBuf, j);
                outFile.write("\n", 1);
                // reset workBuf and j
                j = 0;
                memset(workBuf, '\0', sizeof(workBuf));
            } else { 
                if (mInt > 32 && mInt <= 127) {
                    // printable bytes
                    workBuf[j] = mChar;
                } else {
                    // not printable then use . to replace
                    workBuf[j] = '.'; 
                }
                ++j; // j plus 1
            }
        }
    }

    inFile.close();
    outFile.close();
    exit(0);
}
