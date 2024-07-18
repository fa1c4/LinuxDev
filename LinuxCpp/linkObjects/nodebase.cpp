#include "nodebase.h"

// class NodeBase
// Constructor
NodeBase::NodeBase(): pStr(nullptr) {}

NodeBase::NodeBase(std::string inStr) {
    pStr = new std::string(inStr);
}

NodeBase::NodeBase(const NodeBase& inNode) {
    pStr = new std::string(*inNode.pStr);
}

// Methods
std::string NodeBase::getValue() {
    return *pStr;
}

void NodeBase::setValue(std::string inStr) {
    if (pStr) delete pStr;
    pStr = new std::string(inStr);
}

void NodeBase::displayNodeBase() {
    std::cout << std::setfill(' ') << std::setw(15) << std::left << this << " ";
    std::cout << std::setfill(' ') << std::setw(15) << std::left << this->pStr << " ";
    std::cout << *pStr << std::endl;
}

NodeBase::~NodeBase() {
    if (pStr) delete pStr;
}

// class Node
Node::Node(): linkNode(nullptr) {}

Node::Node(std::string inStr): linkNode(nullptr) {
    setValue(inStr);
}

Node::Node(std::string inStr, Node *pNode) {
    setValue(inStr);
    linkNode = pNode;
}

Node::Node(const Node& inNode): NodeBase(static_cast<NodeBase>(inNode)) {
    linkNode = inNode.linkNode;
}

void Node::Node::displayNode() {
    std::cout << std::setfill(' ') << std::setw(15) << std::left << this << " ";
    std::cout << std::setfill(' ') << std::setw(15) << std::left << this->linkNode << " ";
    std::cout << this->getValue() << std::endl;
}

void Node::setLink(Node *pNode) {
    linkNode = pNode;
}

Node* Node::getLinkNode() {
    return linkNode;
}

Node::~Node() {
    if (linkNode) delete linkNode;
}
