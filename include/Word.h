#ifndef WORD_H
#define WORD_H

class Word {
private:
    char* romanianWord;
    char* englishWord;
    char* wordType;

    char* copyText(const char* text) const;

public:
    Word();
    Word(const char* romanianWord, const char* englishWord, const char* wordType);
    Word(const Word& other);
    Word& operator=(const Word& other);
    ~Word();

    const char* getRomanianWord() const;
    const char* getEnglishWord() const;
    const char* getWordType() const;

    void setRomanianWord(const char* romanianWord);
    void setEnglishWord(const char* englishWord);
    void setWordType(const char* wordType);

    bool matchesRomanian(const char* word) const;
    bool matchesEnglish(const char* word) const;

    void print() const;
};

#endif
