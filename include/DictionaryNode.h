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
    int getIndex() const;
    bool isMarked() const;
    float getWeight() const;

    void setInfo(const Word& info);
    void setNext(DictionaryNode* next);
    void setIndex(int index);
    void setMarked(bool marked);
    void setWeight(float weight);
};

#endif
