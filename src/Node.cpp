#include "../include/Node.h"

Node::Node() : data(), next(0) {
}

Node::Node(const TranslationEntry& entry) : data(entry), next(0) {
}

Node::~Node() {
}

const TranslationEntry& Node::getData() const {
    return data;
}

TranslationEntry& Node::getData() {
    return data;
}

void Node::setData(const TranslationEntry& entry) {
    data = entry;
}

Node* Node::getNext() const {
    return next;
}

void Node::setNext(Node* nextNode) {
    next = nextNode;
}
