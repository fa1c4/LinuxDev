#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <iomanip>
#include <memory>

template <typename mT>

class Node {
private:
    mT *ptrT;
    Node<mT> *linkNode;

public:
    Node(): ptrT(nullptr), linkNode(nullptr) {}

    Node(mT inVal): linkNode(nullptr) {
        ptrT = new mT(inVal);
    }

    Node(mT inVal, Node<mT> *inNode) {
        ptrT = new mT(inVal);
        linkNode = inNode;
    }

    Node(const Node<mT>& inNode) {
        ptrT = new mT(inNode.ptrT);
        linkNode = inNode.linkNode;
    }
    
    ~Node() {
        if (ptrT) delete ptrT;
    }

    mT getValue() {
        return *ptrT;
    }

    Node<mT>* getLinkNode() {
        return linkNode;
    }

    void setValue(mT inVal) {
        if (ptrT) delete ptrT;
        ptrT = new mT(inVal);
    }

    void setLinkNode(Node<mT> *inNode) {
        linkNode = inNode;
    }

    void dispalyNode() {
        std::cout << std::setfill(' ') << std::setw(15) << std::left << this << " ";
        std::cout << std::setfill(' ') << std::setw(15) << std::left << linkNode << " ";
        std::cout << std::setfill(' ') << std::setw(15) << std::left << ptrT << " ";
        std::cout << "-> " << *ptrT << std::endl;;
    }
};

template <typename listType>

class mList {
private:
    Node<listType> *pNode;

public:
    mList(): pNode(nullptr) {}
    
    ~mList() {
        while (pNode) {
            pop_back();
        }
    }

    void push_back(listType inVal) {
        pNode = new Node<listType>(inVal, pNode);
    }

    void pop_back() {
        if (pNode) {
            Node<listType> *curr = pNode;
            pNode = curr->getLinkNode();
            delete curr;
        }
    }

    int size() {
        int ret = 0;
        Node<listType> *curr = pNode;
        while (curr) {
            ret++;
            curr = curr->getLinkNode();
        }

        return ret;
    }

    void displayList() {
        Node<listType> *curr = pNode;
        while (curr) {
            curr->dispalyNode();
            curr = curr->getLinkNode();
        }
    }
};
