#ifndef DICTIONARYNODE_H
#define DICTIONARYNODE_H

#include <iostream>

#include "Word.h"

class DictionaryNode {
private:
    Word info;
    DictionaryNode* next;
    int index;
    bool marked;
    float weight;

public:
    DictionaryNode();
    explicit DictionaryNode(const Word& info, int index = 0, bool marked = false,
                            float weight = 1.0f, DictionaryNode* next = 0);
    ~DictionaryNode();

    const Word& getInfo() const;
    Word& getInfo();
    DictionaryNode* getNext() const;

    void setNext(DictionaryNode* next);
};

#endif
