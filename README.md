# dictionar-traduceri

## Description

`dictionar-traduceri` is a C++ OOP project.
It implements a small Romanian-English dictionary using classes, dynamic memory with `char*`, and a linked list.

## Features

- add a word
- print all words
- search by Romanian word
- delete a word
- update the English translation
- print words by type
- print dictionary information
- print dictionary statistics

## Technologies Used

- C++
- OOP classes
- `char*` and dynamic memory
- singly linked list
- CMake

## How to Build

Make sure you have `cmake` and a C++ compiler installed.

```bash
cmake -S . -B build
cmake --build build
```

## How to Run

After building, run the executable:

```bash
./build/dictionar-traduceri
```

## Design

The project uses four main classes:

### Word

The `Word` class stores the data for one dictionary entry:
- Romanian word
- English word
- word type
- extra information such as id, status, and level

It also contains:
- constructors
- copy constructor
- assignment operator
- destructor
- getters and setters
- `operator<<` and `operator>>`

### DictionaryNode

The `DictionaryNode` class represents one node from the linked list.

Each node contains:
- one `Word` object
- pointer to the next node
- extra node information such as index, marked, and weight

### DictionaryStats

The `DictionaryStats` class stores simple statistics about the dictionary.

Examples:
- total words
- deleted words
- average word length
- type counters

It is used internally by `Dictionary` to recompute and print statistics.

### Dictionary

The `Dictionary` class manages the full linked list of words.

It is responsible for:
- adding words
- searching words
- deleting words
- updating translations
- printing words
- recomputing statistics after changes

The program runs through an interactive console menu from `main.cpp`; the demo function was removed.

This design keeps the original dictionary theme, but extends it so the project covers more OOP requirements.
