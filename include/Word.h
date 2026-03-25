#ifndef WORD_H
#define WORD_H

#include <iostream>

class Word {
private:
    int id;
    char* romanianWord;
    char* englishWord;
    char* wordType;
    bool active;
    char level;

    static int objectCount;

    char* copyText(const char* text) const;

public:
    Word();
    explicit Word(const char* romanianWord, const char* englishWord, const char* wordType,
                  bool active = true, char level = 'A', int id = 0);
    Word(const Word& other);
    Word& operator=(const Word& other);
    ~Word();

    int getId() const;
    const char* getRomanianWord() const;
    const char* getEnglishWord() const;
    const char* getWordType() const;
    bool isActive() const;
    char getLevel() const;

    void setId(int id);
    void setRomanianWord(const char* romanianWord);
    void setEnglishWord(const char* englishWord);
    void setWordType(const char* wordType);
    void setActive(bool active);
    void setLevel(char level);

    bool matchesRomanian(const char* word) const;
    bool matchesEnglish(const char* word) const;
    void changeTranslation(const char* newEnglish);
    int getRomanianLength() const;
    void print() const;

    static int getObjectCount();

    friend std::ostream& operator<<(std::ostream& out, const Word& word);
    friend std::istream& operator>>(std::istream& in, Word& word);
};

#endif
