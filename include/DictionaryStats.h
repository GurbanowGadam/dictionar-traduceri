#ifndef DICTIONARYSTATS_H
#define DICTIONARYSTATS_H

#include <iostream>

class DictionaryStats {
private:
    int totalWords;
    int deletedWords;
    bool changed;
    double averageRomanianLength;
    int* typeCounters;
    int counterSize;

    static int objectCount;

    void allocateCounters(int size);

public:
    DictionaryStats();
    explicit DictionaryStats(int totalWords, int deletedWords, bool changed,
                             double averageRomanianLength, int counterSize = 3);
    DictionaryStats(const DictionaryStats& other);
    DictionaryStats& operator=(const DictionaryStats& other);
    ~DictionaryStats();

    int getTotalWords() const;
    int getDeletedWords() const;
    bool isChanged() const;
    double getAverageRomanianLength() const;
    int getCounterValue(int index) const;

    void setTotalWords(int totalWords);
    void setDeletedWords(int deletedWords);
    void setChanged(bool changed);
    void setAverageRomanianLength(double averageRomanianLength);

    void reset();
    void increaseType(const char* type);
    void decreaseType(const char* type);

    static int getObjectCount();

    friend std::ostream& operator<<(std::ostream& out, const DictionaryStats& stats);
    friend std::istream& operator>>(std::istream& in, DictionaryStats& stats);
};

#endif
