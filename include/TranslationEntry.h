#ifndef TRANSLATIONENTRY_H
#define TRANSLATIONENTRY_H

class TranslationEntry {
private:
    char* romanianWord;
    char* englishWord;
    char* wordType;

    char* copyText(const char* text);

public:
    TranslationEntry();
    TranslationEntry(const char* ro, const char* en, const char* type);
    TranslationEntry(const TranslationEntry& other);
    ~TranslationEntry();

    TranslationEntry& operator=(const TranslationEntry& other);

    const char* getRomanianWord() const;
    const char* getEnglishWord() const;
    const char* getWordType() const;

    void setRomanianWord(const char* ro);
    void setEnglishWord(const char* en);
    void setWordType(const char* type);

    void read();
    void display() const;
};

#endif
