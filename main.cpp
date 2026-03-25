#include <iostream>
#include <limits>

#include "include/Dictionary.h"
#include "include/DictionaryNode.h"
#include "include/DictionaryStats.h"
#include "include/Word.h"

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
    std::cout << "Choice: ";
}

void readText(char text[], int size) {
    std::cin.getline(text, size);
}

void runDemo(Dictionary& dictionary) {
    Word w1("casa", "house", "noun", true, 'A', 0);
    Word w2("apa", "water", "noun", true, 'B', 0);
    Word w3("frumos", "beautiful", "adjective", true, 'A', 0);
    Word w4("a merge", "to walk", "verb", true, 'C', 0);
    DictionaryNode sampleNode(w1, 1, false, 1.5f, 0);
    DictionaryStats sampleStats(2, 1, true, 4.5);

    w1.setLevel('B');
    w1.setActive(true);
    w1.setRomanianWord("casa");
    w1.setWordType("noun");

    sampleNode.setMarked(true);
    sampleNode.setWeight(2.0f);
    sampleStats.setTotalWords(3);
    sampleStats.setDeletedWords(1);
    sampleStats.setChanged(true);
    sampleStats.setAverageRomanianLength(4.0);

    dictionary.addWord(w1);
    dictionary.addWord(w2);
    dictionary.addWord(w3);
    dictionary.addWord(w4);

    std::cout << "Demo:\n";
    std::cout << "Word objects: " << Word::getObjectCount() << "\n";
    std::cout << "Stats objects: " << DictionaryStats::getObjectCount() << "\n";
    std::cout << "Sample node:\n" << sampleNode;
    std::cout << "Sample stats:\n" << sampleStats;
    std::cout << "Dictionary name: " << dictionary.getDictionaryName() << "\n";
    std::cout << "Version: " << dictionary.getVersion() << "\n";
    std::cout << "Next id: " << dictionary.getNextId() << "\n";
    std::cout << "Modified: " << (dictionary.isModified() ? "yes" : "no") << "\n";
    dictionary.printAll();

    std::cout << "\nSearch: apa\n";
    DictionaryNode* foundNode = dictionary.searchRomanian("apa");
    if (foundNode != nullptr) {
        std::cout << foundNode->getInfo();
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
    std::cout << "\nDictionary stats:\n";
    dictionary.printStats();
}

int main() {
    Dictionary dictionary("Romanian-English Dictionary", 1.0f, false, 1);
    runDemo(dictionary);

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
