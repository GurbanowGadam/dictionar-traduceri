#include "../include/Dictionary.h"

#include <cstring>
#include <iostream>

Dictionary::Dictionary() {
    head = nullptr;
}

Dictionary::Dictionary(const Dictionary& other) {
    head = nullptr;
    copyFrom(other);
}

Dictionary& Dictionary::operator=(const Dictionary& other) {
    if (this != &other) {
        Node* current = head;

        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = nullptr;
        copyFrom(other);
    }

    return *this;
}

Dictionary::~Dictionary() {
    Node* current = head;

    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void Dictionary::copyFrom(const Dictionary& other) {
    Node* current = other.head;
    Node* last = nullptr;

    while (current != nullptr) {
        Node* newNode = new Node;
        newNode->info = current->info;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            last->next = newNode;
        }

        last = newNode;
        current = current->next;
    }
}

void Dictionary::addWord(const Word& w) {
    Node* newNode = new Node;
    newNode->info = w;
    newNode->next = head;
    head = newNode;
}

void Dictionary::printAll() const {
    Node* current = head;

    if (current == nullptr) {
        std::cout << "Dictionary is empty.\n";
        return;
    }

    while (current != nullptr) {
        current->info.print();
        std::cout << "\n";
        current = current->next;
    }
}

Dictionary::Node* Dictionary::searchRomanian(const char* word) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->info.matchesRomanian(word)) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

bool Dictionary::deleteWord(const char* word) {
    if (head == nullptr) {
        return false;
    }

    if (head->info.matchesRomanian(word)) {
        Node* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
        return true;
    }

    Node* previous = head;
    Node* current = head->next;

    while (current != nullptr) {
        if (current->info.matchesRomanian(word)) {
            previous->next = current->next;
            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

bool Dictionary::updateEnglishWord(const char* romanian, const char* newEnglish) {
    Node* foundNode = searchRomanian(romanian);

    if (foundNode == nullptr) {
        return false;
    }

    foundNode->info.setEnglishWord(newEnglish);
    return true;
}

void Dictionary::printByType(const char* type) const {
    Node* current = head;
    bool found = false;

    while (current != nullptr) {
        const char* currentType = current->info.getWordType();

        if (currentType != nullptr && type != nullptr && std::strcmp(currentType, type) == 0) {
            current->info.print();
            std::cout << "\n";
            found = true;
        }

        current = current->next;
    }

    if (!found) {
        std::cout << "No match found.\n";
    }
}
