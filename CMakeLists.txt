cmake_minimum_required(VERSION 3.10)

project(dictionar-traduceri)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(dictionar-traduceri
    main.cpp
    src/Word.cpp
    src/DictionaryNode.cpp
    src/DictionaryStats.cpp
    src/Dictionary.cpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(dictionar-traduceri PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
