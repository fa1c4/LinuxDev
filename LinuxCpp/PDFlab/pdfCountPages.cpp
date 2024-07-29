#include "pdfcountpages.h"

#define BUFFER_SIZE 1024
using namespace std;


int main(int argc, char* argv[]) {
    int pgCount = 0;
    int i = 0, j = 0;
    char inBuf[BUFFER_SIZE];
    char workBuf[BUFFER_SIZE];
    char tmpBuf[20];

    // PageTreeNode pTreeNode;

    if (argc != 2) {
        cout << "Usage: pdfCountPage <inPDF file>" << endl;
        exit(1);
    }

    ifstream inFile(argv[1], ios::in | ios::binary);
    if (!inFile.is_open()) {
        cout << "file open error: " << argv[1] << endl;
        exit(-1);
    }

    j = 0, pgCount = 0;
    memset(workBuf, '\0', sizeof(workBuf));
    while (!inFile.eof()) {
        // read all content until eof
        memset(inBuf, '\0', sizeof(inBuf));
        inFile.read(reinterpret_cast<char*>(inBuf), sizeof(inBuf));

        for (i = 0; i < (int)sizeof(inBuf); ++i) {
            char mChar = inBuf[i];
            int mInt = int(mChar);

            if (mChar == 0x0A || j == (BUFFER_SIZE - 1)) {
                // 0x0A is \n
                if (j >= 11) {
                    memset(tmpBuf, '\0', sizeof(tmpBuf));
                    memcpy(tmpBuf, &workBuf[j - 11], 11);
                    if (memcmp(tmpBuf, "/Type./Page", 11) == 0) {
                        // matching for type.page
                        ++pgCount;
                    }
                }

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
    cout << "Total pages of " << argv[1] << ": " << pgCount << endl;

    exit(0);
}
