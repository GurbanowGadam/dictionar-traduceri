#include "../include/Word.h"

#include <cstring>
#include <iostream>

char* Word::copyText(const char* text) const {
    if (text == nullptr) {
        return nullptr;
    }

    char* newText = new char[std::strlen(text) + 1];
    std::strcpy(newText, text);
    return newText;
}

Word::Word() {
    romanianWord = nullptr;
    englishWord = nullptr;
    wordType = nullptr;
}

Word::Word(const char* romanianWord, const char* englishWord, const char* wordType) {
    this->romanianWord = copyText(romanianWord);
    this->englishWord = copyText(englishWord);
    this->wordType = copyText(wordType);
}

Word::Word(const Word& other) {
    romanianWord = copyText(other.romanianWord);
    englishWord = copyText(other.englishWord);
    wordType = copyText(other.wordType);
}

Word& Word::operator=(const Word& other) {
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

Word::~Word() {
    delete[] romanianWord;
    delete[] englishWord;
    delete[] wordType;
}

const char* Word::getRomanianWord() const {
    return romanianWord;
}

const char* Word::getEnglishWord() const {
    return englishWord;
}

const char* Word::getWordType() const {
    return wordType;
}

void Word::setRomanianWord(const char* romanianWord) {
    char* newText = copyText(romanianWord);
    delete[] this->romanianWord;
    this->romanianWord = newText;
}

void Word::setEnglishWord(const char* englishWord) {
    char* newText = copyText(englishWord);
    delete[] this->englishWord;
    this->englishWord = newText;
}

void Word::setWordType(const char* wordType) {
    char* newText = copyText(wordType);
    delete[] this->wordType;
    this->wordType = newText;
}

bool Word::matchesRomanian(const char* word) const {
    if (romanianWord == nullptr || word == nullptr) {
        return false;
    }

    return std::strcmp(romanianWord, word) == 0;
}

bool Word::matchesEnglish(const char* word) const {
    if (englishWord == nullptr || word == nullptr) {
        return false;
    }

    return std::strcmp(englishWord, word) == 0;
}

void Word::print() const {
    std::cout << "Romanian: ";
    if (romanianWord != nullptr) {
        std::cout << romanianWord;
    }
    std::cout << "\n";

    std::cout << "English: ";
    if (englishWord != nullptr) {
        std::cout << englishWord;
    }
    std::cout << "\n";

    std::cout << "Type: ";
    if (wordType != nullptr) {
        std::cout << wordType;
    }
    std::cout << "\n";
}
