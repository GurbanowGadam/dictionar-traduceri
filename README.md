# dictionar-traduceri

## Description

`dictionar-traduceri` is a simple beginner-level C++ OOP project.
It implements a small Romanian-English dictionary using classes, dynamic memory with `char*`, and a linked list.

## Features

- add a word
- print all words
- search by Romanian word
- delete a word
- update the English translation
- print words by type

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

On some systems, the executable name may be slightly different depending on the compiler or platform.

## Design

The project uses two main classes:

### Word

The `Word` class stores:
- Romanian word
- English word
- word type

It uses:
- constructors
- copy constructor
- assignment operator
- destructor
- getters and setters

### Dictionary

The `Dictionary` class stores all words in a singly linked list.

Each node contains:
- one `Word` object
- pointer to the next node

The dictionary is responsible for:
- adding words
- searching words
- deleting words
- updating translations
- printing words

This design is simple and easy to explain for a beginner OOP homework project.
