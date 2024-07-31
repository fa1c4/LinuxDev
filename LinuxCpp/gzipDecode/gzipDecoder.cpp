#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <zlib.h>

#define BUFFER_SIZE 1024 * 8
using namespace std;


int main(int argc, char* argv[]) {
    size_t wIdx = 0;
    struct gzFile_s *mGzFile;

    if (argc != 2) {
        cout << "Usage: gzipDecoder <gzip file>" << endl;
        return 1;
    }

    mGzFile = gzopen(argv[1], "rb");
    if (!mGzFile) {
        cout << "File open error: " << argv[1] << endl;
        return -1;
    }

    if (gzbuffer(mGzFile, BUFFER_SIZE)) {
        cout << "Failed of buffering file: " << argv[1] << endl;
        return -2;
    }

    unsigned char *pInData = new unsigned char[BUFFER_SIZE];
    memset(pInData, '\0', sizeof(*pInData));
    while (!gzeof(mGzFile)) {
        wIdx = gzread(mGzFile, voidp(pInData), BUFFER_SIZE);
        cout << pInData;
    }
    cout << endl;
    cout << "Total Bytes Unzipped: " << wIdx << endl;
    gzclose(mGzFile);
    
    return 0;
}
