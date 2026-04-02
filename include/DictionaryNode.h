#ifndef DICTIONARYNODE_H
#define DICTIONARYNODE_H

#include <iostream>

#include "Word.h"

class DictionaryNode {
private:
    Word info;
    DictionaryNode* next;

public:
    DictionaryNode();
    explicit DictionaryNode(const Word& info, DictionaryNode* next = 0);

    const Word& getInfo() const;
    Word& getInfo();
    DictionaryNode* getNext() const;

    void setNext(DictionaryNode* next);
};

#endif
