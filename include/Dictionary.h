#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>

#include "DictionaryNode.h"
#include "DictionaryStats.h"

class Dictionary {
private:
    DictionaryNode* head;
    char* dictionaryName;
    int nextId;
    bool modified;
    float version;
    DictionaryStats stats;

    char* copyText(const char* text) const;
    void clear();
    void copyFrom(const Dictionary& other);
    void refreshStats();

public:
    Dictionary();
    explicit Dictionary(const char* dictionaryName, float version = 1.0f,
                        bool modified = false, int nextId = 1);
    Dictionary(const Dictionary& other);
    Dictionary& operator=(const Dictionary& other);
    ~Dictionary();

    const char* getDictionaryName() const;
    int getNextId() const;
    bool isModified() const;
    float getVersion() const;
    const DictionaryStats& getStats() const;

    void setDictionaryName(const char* dictionaryName);
    void setVersion(float version);
    void setModified(bool modified);

    void addWord(const Word& word);
    void printAll() const;
    DictionaryNode* searchRomanian(const char* word) const;
    bool deleteWord(const char* word);
    bool updateEnglishWord(const char* romanian, const char* newEnglish);
    void printByType(const char* type) const;
    int countWords() const;
    void printStats() const;

    friend std::ostream& operator<<(std::ostream& out, const Dictionary& dictionary);
    friend std::istream& operator>>(std::istream& in, Dictionary& dictionary);
};

#endif
