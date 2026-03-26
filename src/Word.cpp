#include "../include/Word.h"

#include <cstring>

char* Word::copyText(const char* text) const {
    if (text == 0) {
        char* emptyText = new char[1];
        emptyText[0] = '\0';
        return emptyText;
    }

    char* newText = new char[std::strlen(text) + 1];
    std::strcpy(newText, text);
    return newText;
}

Word::Word() {
    id = 0;
    romanianWord = copyText("");
    englishWord = copyText("");
    wordType = copyText("");
    active = true;
    level = 'A';
}

Word::Word(const char* romanianWord, const char* englishWord, const char* wordType,
           bool active, char level, int id) {
    this->id = id;
    this->romanianWord = copyText(romanianWord);
    this->englishWord = copyText(englishWord);
    this->wordType = copyText(wordType);
    this->active = active;
    this->level = level;
}

Word::Word(const Word& other) {
    id = other.id;
    romanianWord = copyText(other.romanianWord);
    englishWord = copyText(other.englishWord);
    wordType = copyText(other.wordType);
    active = other.active;
    level = other.level;
}

Word& Word::operator=(const Word& other) {
    if (this != &other) {
        char* newRomanian = copyText(other.romanianWord);
        char* newEnglish = copyText(other.englishWord);
        char* newType = copyText(other.wordType);

        delete[] romanianWord;
        delete[] englishWord;
        delete[] wordType;

        id = other.id;
        romanianWord = newRomanian;
        englishWord = newEnglish;
        wordType = newType;
        active = other.active;
        level = other.level;
    }

    return *this;
}

Word::~Word() {
    delete[] romanianWord;
    delete[] englishWord;
    delete[] wordType;
}

int Word::getId() const {
    return id;
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

bool Word::isActive() const {
    return active;
}

char Word::getLevel() const {
    return level;
}

void Word::setId(int id) {
    this->id = id;
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

void Word::setActive(bool active) {
    this->active = active;
}

void Word::setLevel(char level) {
    this->level = level;
}

bool Word::matchesRomanian(const char* word) const {
    if (word == 0) {
        return false;
    }

    return std::strcmp(romanianWord, word) == 0;
}

bool Word::matchesEnglish(const char* word) const {
    if (word == 0) {
        return false;
    }

    return std::strcmp(englishWord, word) == 0;
}

void Word::changeTranslation(const char* newEnglish) {
    setEnglishWord(newEnglish);
}

int Word::getRomanianLength() const {
    return (int)std::strlen(romanianWord);
}

void Word::print() const {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& out, const Word& word) {
    out << "Id: " << word.id << "\n";
    out << "Romanian: " << word.romanianWord << "\n";
    out << "English: " << word.englishWord << "\n";
    out << "Type: " << word.wordType << "\n";
    out << "Active: " << (word.active ? "yes" : "no") << "\n";
    out << "Level: " << word.level << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, Word& word) {
    char romanian[100];
    char english[100];
    char type[100];
    char activeChar;
    char level;

    std::cout << "Romanian word: ";
    in.getline(romanian, 100);

    std::cout << "English word: ";
    in.getline(english, 100);

    std::cout << "Word type: ";
    in.getline(type, 100);

    std::cout << "Active (y/n): ";
    in >> activeChar;
    in.ignore(1000, '\n');

    std::cout << "Level: ";
    in >> level;
    in.ignore(1000, '\n');

    word.setRomanianWord(romanian);
    word.setEnglishWord(english);
    word.setWordType(type);
    word.setActive(activeChar == 'y' || activeChar == 'Y');
    word.setLevel(level);

    return in;
}
