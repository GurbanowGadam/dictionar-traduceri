#include "../include/DictionaryStats.h"

#include <cstring>

int DictionaryStats::objectCount = 0;

void DictionaryStats::allocateCounters(int size) {
    counterSize = size;
    typeCounters = new int[counterSize];

    for (int i = 0; i < counterSize; i++) {
        typeCounters[i] = 0;
    }
}

DictionaryStats::DictionaryStats() {
    totalWords = 0;
    deletedWords = 0;
    changed = false;
    averageRomanianLength = 0.0;
    allocateCounters(3);
    objectCount++;
}

DictionaryStats::DictionaryStats(int totalWords, int deletedWords, bool changed,
                                 double averageRomanianLength, int counterSize) {
    this->totalWords = totalWords;
    this->deletedWords = deletedWords;
    this->changed = changed;
    this->averageRomanianLength = averageRomanianLength;
    allocateCounters(counterSize);
    objectCount++;
}

DictionaryStats::DictionaryStats(const DictionaryStats& other) {
    totalWords = other.totalWords;
    deletedWords = other.deletedWords;
    changed = other.changed;
    averageRomanianLength = other.averageRomanianLength;
    allocateCounters(other.counterSize);

    for (int i = 0; i < counterSize; i++) {
        typeCounters[i] = other.typeCounters[i];
    }

    objectCount++;
}

DictionaryStats& DictionaryStats::operator=(const DictionaryStats& other) {
    if (this != &other) {
        delete[] typeCounters;

        totalWords = other.totalWords;
        deletedWords = other.deletedWords;
        changed = other.changed;
        averageRomanianLength = other.averageRomanianLength;
        allocateCounters(other.counterSize);

        for (int i = 0; i < counterSize; i++) {
            typeCounters[i] = other.typeCounters[i];
        }
    }

    return *this;
}

DictionaryStats::~DictionaryStats() {
    delete[] typeCounters;
    objectCount--;
}

int DictionaryStats::getTotalWords() const {
    return totalWords;
}

int DictionaryStats::getDeletedWords() const {
    return deletedWords;
}

bool DictionaryStats::isChanged() const {
    return changed;
}

double DictionaryStats::getAverageRomanianLength() const {
    return averageRomanianLength;
}

int DictionaryStats::getCounterValue(int index) const {
    if (index < 0 || index >= counterSize) {
        return 0;
    }

    return typeCounters[index];
}

void DictionaryStats::setTotalWords(int totalWords) {
    this->totalWords = totalWords;
}

void DictionaryStats::setDeletedWords(int deletedWords) {
    this->deletedWords = deletedWords;
}

void DictionaryStats::setChanged(bool changed) {
    this->changed = changed;
}

void DictionaryStats::setAverageRomanianLength(double averageRomanianLength) {
    this->averageRomanianLength = averageRomanianLength;
}

void DictionaryStats::reset() {
    totalWords = 0;
    deletedWords = 0;
    changed = false;
    averageRomanianLength = 0.0;

    for (int i = 0; i < counterSize; i++) {
        typeCounters[i] = 0;
    }
}

void DictionaryStats::increaseType(const char* type) {
    if (type == 0) {
        return;
    }

    if (std::strcmp(type, "noun") == 0) {
        typeCounters[0]++;
    } else if (std::strcmp(type, "verb") == 0) {
        typeCounters[1]++;
    } else {
        typeCounters[2]++;
    }
}

void DictionaryStats::decreaseType(const char* type) {
    if (type == 0) {
        return;
    }

    if (std::strcmp(type, "noun") == 0 && typeCounters[0] > 0) {
        typeCounters[0]--;
    } else if (std::strcmp(type, "verb") == 0 && typeCounters[1] > 0) {
        typeCounters[1]--;
    } else if (typeCounters[2] > 0) {
        typeCounters[2]--;
    }
}

int DictionaryStats::getObjectCount() {
    return objectCount;
}

std::ostream& operator<<(std::ostream& out, const DictionaryStats& stats) {
    out << "Total words: " << stats.totalWords << "\n";
    out << "Deleted words: " << stats.deletedWords << "\n";
    out << "Changed: " << (stats.changed ? "yes" : "no") << "\n";
    out << "Average Romanian length: " << stats.averageRomanianLength << "\n";
    out << "Noun count: " << stats.typeCounters[0] << "\n";
    out << "Verb count: " << stats.typeCounters[1] << "\n";
    out << "Other count: " << stats.typeCounters[2] << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, DictionaryStats& stats) {
    int totalWords;
    int deletedWords;
    char changedChar;
    double averageRomanianLength;

    std::cout << "Total words: ";
    in >> totalWords;
    std::cout << "Deleted words: ";
    in >> deletedWords;
    std::cout << "Changed (y/n): ";
    in >> changedChar;
    std::cout << "Average Romanian length: ";
    in >> averageRomanianLength;
    in.ignore(1000, '\n');

    stats.setTotalWords(totalWords);
    stats.setDeletedWords(deletedWords);
    stats.setChanged(changedChar == 'y' || changedChar == 'Y');
    stats.setAverageRomanianLength(averageRomanianLength);

    return in;
}
