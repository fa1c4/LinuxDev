#include "templateLinkList.h"


int main() {
    mList<std::string> mListInst;
    mListInst.push_back("List Object 1");
    mListInst.push_back("List Object 2");
    mListInst.push_back("List Object 3");
    mListInst.push_back("List Object 4");
    mListInst.push_back("List Object 5");
    mListInst.push_back("List Object 6");

    for (auto it = mListInst.begin(); it != mListInst.end(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << "mListInst size is: " << mListInst.size() << std::endl;
    std::cout << "----------------------" << std::endl;

    mListInst.pop_back();
    mListInst.pop_back();

    for (auto it = mListInst.begin(); it != mListInst.end(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << "mListInst size is: " << mListInst.size() << std::endl;
    std::cout << "----------------------" << std::endl;

    return 0;
}
