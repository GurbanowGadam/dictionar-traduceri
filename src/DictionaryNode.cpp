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

int DictionaryNode::getIndex() const {
    return index;
}

bool DictionaryNode::isMarked() const {
    return marked;
}

float DictionaryNode::getWeight() const {
    return weight;
}

void DictionaryNode::setInfo(const Word& info) {
    this->info = info;
}

void DictionaryNode::setNext(DictionaryNode* next) {
    this->next = next;
}

void DictionaryNode::setIndex(int index) {
    this->index = index;
}

void DictionaryNode::setMarked(bool marked) {
    this->marked = marked;
}

void DictionaryNode::setWeight(float weight) {
    this->weight = weight;
}
