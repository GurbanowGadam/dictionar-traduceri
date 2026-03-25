#include <iostream>
#include <limits>

#include "include/Dictionary.h"
#include "include/Word.h"

void printMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add word\n";
    std::cout << "2. Print all words\n";
    std::cout << "3. Search Romanian word\n";
    std::cout << "4. Delete word\n";
    std::cout << "5. Update English translation\n";
    std::cout << "6. Print words by type\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

void readText(char text[], int size) {
    std::cin.getline(text, size);
}

void runDemo(Dictionary& dictionary) {
    Word w1("casa", "house", "noun");
    Word w2("apa", "water", "noun");
    Word w3("frumos", "beautiful", "adjective");
    Word w4("a merge", "to walk", "verb");

    dictionary.addWord(w1);
    dictionary.addWord(w2);
    dictionary.addWord(w3);
    dictionary.addWord(w4);

    std::cout << "Demo:\n";
    dictionary.printAll();

    std::cout << "\nSearch: apa\n";
    Dictionary::Node* foundNode = dictionary.searchRomanian("apa");
    if (foundNode != nullptr) {
        foundNode->info.print();
    } else {
        std::cout << "Not found.\n";
    }

    std::cout << "\nUpdate casa -> home\n";
    if (dictionary.updateEnglishWord("casa", "home")) {
        std::cout << "Updated.\n";
    } else {
        std::cout << "Not found.\n";
    }

    std::cout << "\nType: noun\n";
    dictionary.printByType("noun");

    std::cout << "\nDelete: frumos\n";
    if (dictionary.deleteWord("frumos")) {
        std::cout << "Deleted.\n";
    } else {
        std::cout << "Not found.\n";
    }

    std::cout << "\nAfter delete:\n";
    dictionary.printAll();
}

int main() {
    Dictionary dictionary;
    // runDemo(dictionary);

    int choice;

    do {
        char romanian[100];
        char english[100];
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
            std::cout << "Romanian word: ";
            readText(romanian, 100);

            std::cout << "English word: ";
            readText(english, 100);

            std::cout << "Word type: ";
            readText(type, 100);

            Word newWord(romanian, english, type);
            dictionary.addWord(newWord);
            std::cout << "Added.\n";
        } else if (choice == 2) {
            dictionary.printAll();
        } else if (choice == 3) {
            std::cout << "Romanian word: ";
            readText(romanian, 100);

            Dictionary::Node* foundNode = dictionary.searchRomanian(romanian);
            if (foundNode != nullptr) {
                foundNode->info.print();
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
        } else if (choice != 0) {
            std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
