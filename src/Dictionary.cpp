#include "../include/Dictionary.h"

#include <cstring>

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

void Dictionary::setDictionaryName(const char* dictionaryName) {
    char* newText = copyText(dictionaryName);
    delete[] this->dictionaryName;
    this->dictionaryName = newText;
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

    DictionaryNode* newNode = new DictionaryNode(copyWord, countWords() + 1, false, 1.0f, head);
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

    dictionary.setDictionaryName(name);
    dictionary.setVersion(version);

    return in;
}
