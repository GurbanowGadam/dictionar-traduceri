#include "../include/TranslationEntry.h"

#include <cstring>
#include <iostream>

char* TranslationEntry::copyText(const char* text) {
    if (text == 0) {
        char* emptyText = new char[1];
        emptyText[0] = '\0';
        return emptyText;
    }

    char* newText = new char[std::strlen(text) + 1];
    std::strcpy(newText, text);
    return newText;
}

TranslationEntry::TranslationEntry() {
    romanianWord = copyText("");
    englishWord = copyText("");
    wordType = copyText("");
}

TranslationEntry::TranslationEntry(const char* ro, const char* en, const char* type) {
    romanianWord = copyText(ro);
    englishWord = copyText(en);
    wordType = copyText(type);
}

TranslationEntry::TranslationEntry(const TranslationEntry& other) {
    romanianWord = copyText(other.romanianWord);
    englishWord = copyText(other.englishWord);
    wordType = copyText(other.wordType);
}

TranslationEntry::~TranslationEntry() {
    delete[] romanianWord;
    delete[] englishWord;
    delete[] wordType;
}

TranslationEntry& TranslationEntry::operator=(const TranslationEntry& other) {
    if (this != &other) {
        delete[] romanianWord;
        delete[] englishWord;
        delete[] wordType;

        romanianWord = copyText(other.romanianWord);
        englishWord = copyText(other.englishWord);
        wordType = copyText(other.wordType);
    }

    return *this;
}

const char* TranslationEntry::getRomanianWord() const {
    return romanianWord;
}

const char* TranslationEntry::getEnglishWord() const {
    return englishWord;
}

const char* TranslationEntry::getWordType() const {
    return wordType;
}

void TranslationEntry::setRomanianWord(const char* ro) {
    delete[] romanianWord;
    romanianWord = copyText(ro);
}

void TranslationEntry::setEnglishWord(const char* en) {
    delete[] englishWord;
    englishWord = copyText(en);
}

void TranslationEntry::setWordType(const char* type) {
    delete[] wordType;
    wordType = copyText(type);
}

void TranslationEntry::read() {
    char bufferRo[100];
    char bufferEn[100];
    char bufferType[100];

    std::cout << "Romanian word: ";
    std::cin.getline(bufferRo, 100);

    std::cout << "English word: ";
    std::cin.getline(bufferEn, 100);

    std::cout << "Word type: ";
    std::cin.getline(bufferType, 100);

    setRomanianWord(bufferRo);
    setEnglishWord(bufferEn);
    setWordType(bufferType);
}

void TranslationEntry::display() const {
    std::cout << "Romanian: " << romanianWord << "\n";
    std::cout << "English: " << englishWord << "\n";
    std::cout << "Type: " << wordType << "\n";
}
