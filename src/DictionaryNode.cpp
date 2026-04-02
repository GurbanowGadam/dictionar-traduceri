#include "../include/DictionaryNode.h"

DictionaryNode::DictionaryNode() : info(), next(0), index(0), marked(false), weight(1.0f) {
}

DictionaryNode::DictionaryNode(const Word& info, int index, bool marked,
                               float weight, DictionaryNode* next)
    : info(info), next(next), index(index), marked(marked), weight(weight) {
}

DictionaryNode::~DictionaryNode() {
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
