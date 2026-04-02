#include "../include/DictionaryNode.h"

DictionaryNode::DictionaryNode() : info(), next(0) {
}

DictionaryNode::DictionaryNode(const Word& info, DictionaryNode* next)
    : info(info), next(next) {
}

const Word& DictionaryNode::getInfo() const {
    return info;
}

Word& DictionaryNode::getInfo() {
    return info;
}

DictionaryNode* DictionaryNode::getNext() const {
    return next;
}

void DictionaryNode::setNext(DictionaryNode* next) {
    this->next = next;
}
