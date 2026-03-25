#ifndef NODE_H
#define NODE_H

#include "TranslationEntry.h"

class Node {
private:
    TranslationEntry data;
    Node* next;

public:
    Node();
    Node(const TranslationEntry& entry);
    ~Node();

    const TranslationEntry& getData() const;
    TranslationEntry& getData();
    void setData(const TranslationEntry& entry);

    Node* getNext() const;
    void setNext(Node* nextNode);
};

#endif
