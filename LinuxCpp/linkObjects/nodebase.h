#ifndef NODEBASE_H
#define NODEBASE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <stdlib.h>

class NodeBase {
public:
    // Constructor
    NodeBase();
    NodeBase(std::string inStr);
    NodeBase(const NodeBase& inNode);

    // Methods
    std::string getValue();
    void setValue(std::string inStr);
    void displayNodeBase();
    virtual ~NodeBase();

private:
    std::string *pStr;
};

class Node: public NodeBase {
public:
    Node();
    Node(std::string inStr);
    Node(std::string inStr, Node *pNode);
    Node(const Node& inNode);
    void setLink(Node *pNode);
    Node* getLinkNode();
    void displayNode();
    ~Node();

private:
    Node *linkNode;
};

#endif // ODEBASE_H
