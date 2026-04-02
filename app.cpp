#include <cstring>
#include <iostream>
#include <limits>

class Word {
private:
    int id;
    char* romanianWord;
    char* englishWord;
    char* wordType;
    bool active;
    char level;

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

    friend std::ostream& operator<<(std::ostream& out, const Word& word);
    friend std::istream& operator>>(std::istream& in, Word& word);
};

class DictionaryNode {
private:
    Word info;
    DictionaryNode* next;

public:
    DictionaryNode();
    explicit DictionaryNode(const Word& info, DictionaryNode* next = 0);

    const Word& getInfo() const;
    Word& getInfo();
    DictionaryNode* getNext() const;

    void setNext(DictionaryNode* next);
};

class DictionaryStats {
private:
    int totalWords;
    int deletedWords;
    bool changed;
    double averageRomanianLength;
    int* typeCounters;
    int counterSize;

    void allocateCounters(int size);

public:
    DictionaryStats();
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

    friend std::ostream& operator<<(std::ostream& out, const DictionaryStats& stats);
};

class Dictionary {
private:
    DictionaryNode* head;
    char* dictionaryName;
    int nextId;
    float version;
    DictionaryStats stats;

    char* copyText(const char* text) const;
    void clear();
    void refreshStats();

public:
    Dictionary();
    explicit Dictionary(const char* dictionaryName, float version = 1.0f, int nextId = 1);
    ~Dictionary();

    const char* getDictionaryName() const;
    int getNextId() const;
    float getVersion() const;

    void setVersion(float version);

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

DictionaryNode::DictionaryNode() : info(), next(0) {
}

DictionaryNode::DictionaryNode(const Word& info, DictionaryNode* next)
    : info(info), next(next) {
}

const Word& DictionaryNode::getInfo() const {
    return info;
}

Word& DictionaryNode::getInfo() {
    return info;
}

DictionaryNode* DictionaryNode::getNext() const {
    return next;
}

void DictionaryNode::setNext(DictionaryNode* next) {
    this->next = next;
}

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

char* Dictionary::copyText(const char* text) const {
    if (text == 0) {
        char* emptyText = new char[1];
        emptyText[0] = '\0';
        return emptyText;
    }

    char* newText = new char[std::strlen(text) + 1];
    std::strcpy(newText, text);
    return newText;
}

Dictionary::Dictionary() : stats() {
    head = 0;
    dictionaryName = copyText("Romanian-English Dictionary");
    nextId = 1;
    version = 1.0f;
}

Dictionary::Dictionary(const char* dictionaryName, float version, int nextId)
    : stats() {
    head = 0;
    this->dictionaryName = copyText(dictionaryName);
    this->nextId = nextId;
    this->version = version;
}

Dictionary::~Dictionary() {
    clear();
    delete[] dictionaryName;
}

void Dictionary::clear() {
    DictionaryNode* current = head;

    while (current != 0) {
        DictionaryNode* nextNode = current->getNext();
        delete current;
        current = nextNode;
    }

    head = 0;
}

void Dictionary::refreshStats() {
    int deletedCount = stats.getDeletedWords();
    bool changedValue = stats.isChanged();

    stats.reset();
    stats.setDeletedWords(deletedCount);
    stats.setChanged(changedValue);

    int totalLength = 0;
    DictionaryNode* current = head;

    while (current != 0) {
        stats.setTotalWords(stats.getTotalWords() + 1);
        stats.increaseType(current->getInfo().getWordType());
        totalLength += current->getInfo().getRomanianLength();
        current = current->getNext();
    }

    if (stats.getTotalWords() > 0) {
        stats.setAverageRomanianLength((double)totalLength / stats.getTotalWords());
    }
}

const char* Dictionary::getDictionaryName() const {
    return dictionaryName;
}

int Dictionary::getNextId() const {
    return nextId;
}

float Dictionary::getVersion() const {
    return version;
}

void Dictionary::setVersion(float version) {
    this->version = version;
}

void Dictionary::addWord(const Word& word) {
    Word copyWord(word);

    if (copyWord.getId() == 0) {
        copyWord.setId(nextId);
        nextId++;
    }

    DictionaryNode* newNode = new DictionaryNode(copyWord, head);
    head = newNode;
    refreshStats();
    stats.setChanged(true);
}

void Dictionary::printAll() const {
    DictionaryNode* current = head;

    if (current == 0) {
        std::cout << "Dictionary is empty.\n";
        return;
    }

    while (current != 0) {
        std::cout << current->getInfo();
        std::cout << "--------------------\n";
        current = current->getNext();
    }
}

DictionaryNode* Dictionary::searchRomanian(const char* word) const {
    DictionaryNode* current = head;

    while (current != 0) {
        if (current->getInfo().matchesRomanian(word)) {
            return current;
        }

        current = current->getNext();
    }

    return 0;
}

bool Dictionary::deleteWord(const char* word) {
    if (head == 0) {
        return false;
    }

    if (head->getInfo().matchesRomanian(word)) {
        DictionaryNode* nodeToDelete = head;
        head = head->getNext();
        stats.setDeletedWords(stats.getDeletedWords() + 1);
        delete nodeToDelete;
        refreshStats();
        stats.setChanged(true);
        return true;
    }

    DictionaryNode* previous = head;
    DictionaryNode* current = head->getNext();

    while (current != 0) {
        if (current->getInfo().matchesRomanian(word)) {
            previous->setNext(current->getNext());
            stats.setDeletedWords(stats.getDeletedWords() + 1);
            delete current;
            refreshStats();
            stats.setChanged(true);
            return true;
        }

        previous = current;
        current = current->getNext();
    }

    return false;
}

bool Dictionary::updateEnglishWord(const char* romanian, const char* newEnglish) {
    DictionaryNode* foundNode = searchRomanian(romanian);

    if (foundNode == 0) {
        return false;
    }

    foundNode->getInfo().changeTranslation(newEnglish);
    stats.setChanged(true);
    return true;
}

void Dictionary::printByType(const char* type) const {
    DictionaryNode* current = head;
    bool found = false;

    while (current != 0) {
        if (std::strcmp(current->getInfo().getWordType(), type) == 0) {
            std::cout << current->getInfo();
            std::cout << "--------------------\n";
            found = true;
        }

        current = current->getNext();
    }

    if (!found) {
        std::cout << "No match found.\n";
    }
}

int Dictionary::countWords() const {
    int count = 0;
    DictionaryNode* current = head;

    while (current != 0) {
        count++;
        current = current->getNext();
    }

    return count;
}

void Dictionary::printStats() const {
    std::cout << stats;
}

std::ostream& operator<<(std::ostream& out, const Dictionary& dictionary) {
    out << "Name: " << dictionary.dictionaryName << "\n";
    out << "Next id: " << dictionary.nextId << "\n";
    out << "Version: " << dictionary.version << "\n";
    out << dictionary.stats;
    return out;
}

std::istream& operator>>(std::istream& in, Dictionary& dictionary) {
    char name[100];
    float version;

    std::cout << "Dictionary name: ";
    in.getline(name, 100);

    std::cout << "Version: ";
    in >> version;
    in.ignore(1000, '\n');

    char* newName = dictionary.copyText(name);
    delete[] dictionary.dictionaryName;
    dictionary.dictionaryName = newName;
    dictionary.setVersion(version);

    return in;
}

void printMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add word\n";
    std::cout << "2. Print all words\n";
    std::cout << "3. Search Romanian word\n";
    std::cout << "4. Delete word\n";
    std::cout << "5. Update English translation\n";
    std::cout << "6. Print words by type\n";
    std::cout << "7. Print dictionary info\n";
    std::cout << "8. Change dictionary info\n";
    std::cout << "9. Print statistics\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: \n\n";
}

void readText(char text[], int size) {
    std::cin.getline(text, size);
}

int main() {
    Dictionary dictionary("Romanian-English Dictionary", 1.0f, 1);

    int choice;

    do {
        char romanian[100];
        char type[100];

        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid option.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            Word newWord;
            std::cin >> newWord;
            dictionary.addWord(newWord);
            std::cout << "Added.\n";
        } else if (choice == 2) {
            dictionary.printAll();
        } else if (choice == 3) {
            std::cout << "Romanian word: ";
            readText(romanian, 100);

            DictionaryNode* foundNode = dictionary.searchRomanian(romanian);
            if (foundNode != nullptr) {
                std::cout << foundNode->getInfo();
            } else {
                std::cout << "Not found.\n";
            }
        } else if (choice == 4) {
            std::cout << "Romanian word: ";
            readText(romanian, 100);

            if (dictionary.deleteWord(romanian)) {
                std::cout << "Deleted.\n";
            } else {
                std::cout << "Not found.\n";
            }
        } else if (choice == 5) {
            char english[100];
            std::cout << "Romanian word: ";
            readText(romanian, 100);

            std::cout << "New English word: ";
            readText(english, 100);

            if (dictionary.updateEnglishWord(romanian, english)) {
                std::cout << "Updated.\n";
            } else {
                std::cout << "Not found.\n";
            }
        } else if (choice == 6) {
            std::cout << "Word type: ";
            readText(type, 100);
            dictionary.printByType(type);
        } else if (choice == 7) {
            std::cout << dictionary;
        } else if (choice == 8) {
            std::cin >> dictionary;
            std::cout << "Dictionary updated.\n";
        } else if (choice == 9) {
            dictionary.printStats();
        } else if (choice != 0) {
            std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
