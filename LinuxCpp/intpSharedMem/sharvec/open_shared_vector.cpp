#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace boost::interprocess;


typedef allocator<int, managed_shared_memory::segment_manager> mAllocator;
typedef vector<int, mAllocator> mVectorType;


int main () {
    int vecSize = 0;
    char opt[32];
    memset(opt, '\0', sizeof(opt));

    managed_shared_memory segment(open_only, "mSharedMemory");
    mVectorType *mVector = segment.find<mVectorType>("mVector").first;
    
    vecSize = mVector->size();
    for (int i = 0; i < vecSize; ++i) {
        if (i < vecSize - 1) std::cout << mVector->at(i) << ", ";
        else std::cout << mVector->at(i) << std::endl;
    }

    while (true) {
        std::cout << "Select Option (increase | read | push | pop | exit): ";
        memset(opt, 0, sizeof(opt));
        std::cin.getline(opt, sizeof(opt));
        vecSize = mVector->size();

        if (!strcmp(opt, "increase")) {
            for (int i = 0; i < vecSize; ++i) {
                mVector->at(i)++;
            }
        } else if (!strcmp(opt, "read")) {
            for (int i = 0; i < vecSize; ++i) {
                if (i < vecSize - 1) std::cout << mVector->at(i) << ", ";
                else std::cout << mVector->at(i) << std::endl;
            }
        } else if (!strcmp(opt, "push")) {
            int input_val = 0;
            char input_buf[32]; // buffer to hold the input string
            std::cout << "the value to input: ";
            std::cin.getline(input_buf, sizeof(input_buf)); // read as a string
            input_val = std::atoi(input_buf); // convert to integer
            mVector->push_back(input_val);
        } else if (!strcmp(opt, "pop")) {
            mVector->pop_back();
        } else { // "exit"
            break;
        }
    }

    return 0;
}
