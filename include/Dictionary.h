#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Word.h"

class Dictionary {
public:
    struct Node {
        Word info;
        Node* next;
    };

private:
    Node* head;

    void copyFrom(const Dictionary& other);

public:
    Dictionary();
    Dictionary(const Dictionary& other);
    Dictionary& operator=(const Dictionary& other);
    ~Dictionary();

    void addWord(const Word& w);
    void printAll() const;
    Node* searchRomanian(const char* word) const;
    bool deleteWord(const char* word);
    bool updateEnglishWord(const char* romanian, const char* newEnglish);
    void printByType(const char* type) const;
};

#endif
