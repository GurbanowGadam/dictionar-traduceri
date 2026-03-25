#include "../include/DictionaryNode.h"

DictionaryNode::DictionaryNode() : info(), next(0), index(0), marked(false), weight(1.0f) {
}

DictionaryNode::DictionaryNode(const Word& info, int index, bool marked,
                               float weight, DictionaryNode* next)
    : info(info), next(next), index(index), marked(marked), weight(weight) {
}

DictionaryNode::DictionaryNode(const DictionaryNode& other)
    : info(other.info), next(other.next), index(other.index),
      marked(other.marked), weight(other.weight) {
}

DictionaryNode& DictionaryNode::operator=(const DictionaryNode& other) {
    if (this != &other) {
        info = other.info;
        next = other.next;
        index = other.index;
        marked = other.marked;
        weight = other.weight;
    }

    return *this;
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

std::ostream& operator<<(std::ostream& out, const DictionaryNode& node) {
    out << node.info;
    out << "Index: " << node.index << "\n";
    out << "Marked: " << (node.marked ? "yes" : "no") << "\n";
    out << "Weight: " << node.weight << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, DictionaryNode& node) {
    Word word;
    int index;
    char markedChar;
    float weight;

    in >> word;
    std::cout << "Node index: ";
    in >> index;
    in.ignore(1000, '\n');

    std::cout << "Marked (y/n): ";
    in >> markedChar;
    in.ignore(1000, '\n');

    std::cout << "Weight: ";
    in >> weight;
    in.ignore(1000, '\n');

    node.setInfo(word);
    node.setIndex(index);
    node.setMarked(markedChar == 'y' || markedChar == 'Y');
    node.setWeight(weight);
    node.setNext(0);

    return in;
}
