#include <iostream>
#include <string>
#include <cstring>


enum ProcStatus {
    INIT,
    START_OBJECTING,
    START_STREAMING,
    END_COPYING,
    END_STREAMING,
    END_OBJECTING
};

struct processPDF {
    ProcStatus wStat = INIT;
    int currLine = 0;
    int currObjID = 0;
    int currObjGen = 0;
    int streamLenData = 0;
    int streamLenDest = 0;
    unsigned char* pstrmData = nullptr;
    unsigned char* pstrmDest = nullptr;
    std::string* Filter = nullptr;
};

// Function to clean up the struct
void cleanUpProcessPDF(processPDF& mPDF) {
    // Safely delete dynamically allocated memory
    if (mPDF.pstrmData) {
        std::cout << "Deleting pstrmData" << std::endl;
        delete[] mPDF.pstrmData;
        mPDF.pstrmData = nullptr;
    }
    if (mPDF.pstrmDest) {
        std::cout << "Deleting pstrmDest" << std::endl;
        delete[] mPDF.pstrmDest;
        mPDF.pstrmDest = nullptr;
    }
    if (mPDF.Filter) {
        std::cout << "Deleting Filter" << std::endl;
        delete mPDF.Filter;
        mPDF.Filter = nullptr;
    }
}

int main() {
    processPDF mPDF;

    // Example allocation (for demonstration)
    mPDF.pstrmData = new unsigned char[100];
    mPDF.pstrmDest = new unsigned char[200];
    mPDF.Filter = new std::string("ExampleFilter");

    // Use mPDF...

    // Clean up the allocated memory
    cleanUpProcessPDF(mPDF);

    return 0;
}
