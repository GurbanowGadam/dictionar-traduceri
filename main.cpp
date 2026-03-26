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
    Dictionary dictionary("Romanian-English Dictionary", 1.0f, false, 1);

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
