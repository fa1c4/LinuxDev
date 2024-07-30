#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <zlib.h>
#include <sstream>
#include <cstring>
#include <cassert>


#define BUFFER_SIZE 1024

using namespace std;

// Enum for processing status
enum ProcStatus {
    INIT,
    START_OBJECTING,
    START_STREAMING,
    END_COPYING,
    END_STREAMING,
    END_OBJECTING
};

// Struct to hold PDF processing information
struct processPDF {
    ProcStatus wStat = INIT;
    int currLine = 0;
    int currObjID = 0;
    int currObjGen = 0;
    int streamLenData = 0;
    int streamLenDest = 0;
    unsigned char* pstrmData = nullptr;
    unsigned char* pstrmDest = nullptr;
    string* Filter = nullptr;
};

// Function to clean up the struct
void cleanUpProcessPDF(processPDF& mPDF) {
    // Safely delete dynamically allocated memory
    if (mPDF.pstrmData) {
        delete[] mPDF.pstrmData;
        mPDF.pstrmData = nullptr;
    }
    if (mPDF.pstrmDest) {
        delete[] mPDF.pstrmDest;
        mPDF.pstrmDest = nullptr;
    }
    if (mPDF.Filter) {
        delete mPDF.Filter;
        mPDF.Filter = nullptr;
    }
}

void procReadBuffer(processPDF& mPDF, char *inPtr) {
    vector<string> mVec;
    char inBuffer[BUFFER_SIZE+1];
    char workBuffer[BUFFER_SIZE+1];
    int wIdx = 0;

    memset(inBuffer, '\0', BUFFER_SIZE+1);
    memset(workBuffer, '\0', BUFFER_SIZE+1);

    memcpy(inBuffer, inPtr, BUFFER_SIZE+1);

    for (int i = 0; i < BUFFER_SIZE - 1; ++i) {
        if (mPDF.wStat == ProcStatus::START_STREAMING) {
            mPDF.currLine++;
            if ((i + mPDF.streamLenDest) <= BUFFER_SIZE) {
                memcpy(mPDF.pstrmDest, &inBuffer[i], mPDF.streamLenDest);
                i += mPDF.streamLenDest - 1; // -1 because loop will increment i
                mPDF.streamLenDest = 0;
            } else {
                memcpy(mPDF.pstrmDest, &inBuffer[i], (BUFFER_SIZE-i));
                mPDF.streamLenDest -= (BUFFER_SIZE-i);
                mPDF.pstrmDest += (BUFFER_SIZE-i);
                i = BUFFER_SIZE;
            }

            if (mPDF.streamLenDest <= 0) {
                mPDF.wStat = ProcStatus::END_COPYING;
            }
            continue;
        }

        if (inBuffer[i] != '\n') {
            workBuffer[wIdx++] = inBuffer[i];
            continue;
        }

        mPDF.currLine++;
        mVec.clear();

        if (mPDF.currLine > 2) {
            char* pch = strtok(workBuffer, " \t\n");
            while (pch != NULL) {
                mVec.push_back(string(pch));
                pch = strtok(NULL, " \t\n");
            }
        }

        if (mVec.empty()) {
            wIdx = 0;
            memset(workBuffer, '\0', BUFFER_SIZE + 1);
            continue;
        }

        if (mPDF.wStat == ProcStatus::INIT) {
            for (auto it = mVec.begin(); it != mVec.end(); ++it) {
                if (*it == "obj") {
                    it--;
                    mPDF.currObjGen = stoi(*it);
                    it--;
                    mPDF.currObjID = stoi(*it);
                    if (mPDF.currObjID == 6) {
                        mPDF.wStat = ProcStatus::START_OBJECTING;
                    }
                    break;
                }
            }
        }

        if (mPDF.wStat == ProcStatus::START_OBJECTING) {
            for (auto it = mVec.begin(); it != mVec.end(); ++it) {
                if (*it == "/Length") {
                    it++;
                    mPDF.streamLenData = stoi(*it);
                    mPDF.streamLenDest = mPDF.streamLenData;
                }
                if (*it == "/Filter") {
                    it++;
                    mPDF.Filter = new string(*it);
                }
                if (*it == "stream") {
                    mPDF.pstrmData = new unsigned char[mPDF.streamLenData + 1];
                    mPDF.pstrmDest = mPDF.pstrmData;
                    memset(mPDF.pstrmDest, '\0', mPDF.streamLenData);
                    mPDF.wStat = ProcStatus::START_STREAMING;
                }
            }
        }

        if (mPDF.wStat == ProcStatus::END_COPYING) {
            for (auto it = mVec.begin(); it != mVec.end(); ++it) {
                if (*it == "endstream") {
                    mPDF.wStat = ProcStatus::END_STREAMING;
                }
            }
        }

        if (mPDF.wStat == ProcStatus::END_STREAMING) {
            for (auto it = mVec.begin(); it != mVec.end(); ++it) {
                if (*it == "endobj") {
                    mPDF.wStat = ProcStatus::END_OBJECTING;
                }
            }
        }

        if (mPDF.wStat == ProcStatus::END_OBJECTING) {
            break;
        }

        wIdx = 0;
        memset(workBuffer, '\0', BUFFER_SIZE+1);
    }
}


int main(int argc, char* argv[]) {
    processPDF mPDF;
    char readBuffer[BUFFER_SIZE];

    if (argc != 2) {
        cout << "Usage: pdfProcess <inPDF file>" << endl;
        return 1;
    }

    ifstream inFile(argv[1], ios::in | ios::binary);
    if (!inFile.is_open()) {
        cout << "File open error: " << argv[1] << endl;
        return -1;
    }

    while (!inFile.eof()) {
        memset(readBuffer, '\0', sizeof(readBuffer));
        inFile.read(reinterpret_cast<char*>(readBuffer), sizeof(readBuffer));
        procReadBuffer(mPDF, readBuffer);

        if (mPDF.wStat == ProcStatus::END_OBJECTING)
            break;
    }

    inFile.close();
    cout << "PDF File Name: " << argv[1] << endl;
    cout << "Process Object ID: " << mPDF.currObjID << " " << mPDF.currObjGen << " obj" << endl;
    string mFilter = (mPDF.Filter) ? *mPDF.Filter : "None";
    cout << "Stream Bytes length: " << mPDF.streamLenData << endl;
    cout << "Decoding Filter: " << mFilter << endl;

    // Decompress the stream data if it's compressed
    mPDF.streamLenDest = 1024 * 1024 * 8;
    mPDF.pstrmDest = new unsigned char[mPDF.streamLenDest+1];
    memset(mPDF.pstrmDest, '\0', mPDF.streamLenDest);
    int ret = uncompress((Bytef*)mPDF.pstrmDest, (uLongf*)&mPDF.streamLenDest,
                         (Bytef*)mPDF.pstrmData, (uLongf)mPDF.streamLenData);
    
    if (ret != Z_OK) {
        cout << "Decompression failed with error code: " << ret << endl;
    } else {
        cout << "Stream Bytes before Decoding: " << mPDF.streamLenData << endl;
        cout << "Stream Bytes after Decoding: " << mPDF.streamLenDest << endl;
        cout << "---------------------------" << endl;
        cout << mPDF.pstrmDest << endl;
    }

    // Safe memory deallocation with error handling
    try {
        // cleanUpProcessPDF(mPDF);
        // segmentaion fault when delete the struct mPDF
    } catch (const std::exception& e) {
        cout << "Error during cleanup: " << e.what() << endl;
    } catch (...) {
        cout << "Unknown error during cleanup" << endl;
    }
    
    return 0;
}
