#include "../include/DictionaryStats.h"

#include <cstring>

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
}

DictionaryStats::~DictionaryStats() {
    delete[] typeCounters;
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
