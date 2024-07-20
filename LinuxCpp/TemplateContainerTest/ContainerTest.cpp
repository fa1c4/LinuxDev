#include "templateLinkList.h"


/*
    std::list<std::string> mList;
    mList.push_back("List Object 1");
    mList.push_back("List Object 2");
    mList.push_back("List Object 3");
    mList.push_back("List Object 4");
    mList.push_back("List Object 5");
    mList.push_back("List Object 6");

    for (auto it = mList.rbegin(); it != mList.rend(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << "----------------------" << std::endl;
    std::cout << "mList size is: " << mList.size() << std::endl;

    mList.pop_back();
    mList.pop_back();

    for (auto it = mList.rbegin(); it != mList.rend(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << "----------------------" << std::endl;
    std::cout << "mList size is: " << mList.size() << std::endl;
*/

int main() {
    mList<std::string> mListInst;
    mListInst.push_back("List Object 1");
    mListInst.push_back("List Object 2");
    mListInst.push_back("List Object 3");
    mListInst.push_back("List Object 4");
    mListInst.push_back("List Object 5");
    mListInst.push_back("List Object 6");

    mListInst.displayList();
    std::cout << "mListInst size is: " << mListInst.size() << std::endl;
    std::cout << "----------------------" << std::endl;

    mListInst.pop_back();
    mListInst.pop_back();
    mListInst.displayList();
    std::cout << "mListInst size is: " << mListInst.size() << std::endl;
    std::cout << "----------------------" << std::endl;

    return 0;
}
