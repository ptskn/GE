//
// Created by ptskn on 16/09/2025.
//
#include "ClangTokensExtractor.h"
static int tester(const std::string &headerContent, const std::string &sourceContent) {
    ClangTokensExtractor extractor;
/*
    std::string headerContent = R"(
        #pragma once
        #define MAX_SIZE 100
        #define DEBUG_MODE
        #ifdef DEBUG_MODE
        #include <iostream>
        #endif
        enum class Color { Red, Green, Blue };
        class MyClass {
        public:
            void foo(int x);
        };
    )";

    std::string sourceContent = R"(
        #include "temp_header.h"
        void MyClass::foo(int x) {
            #ifdef DEBUG_MODE
            std::cout << "Debug mode: " << MAX_SIZE << "\n";
            #endif
            Color c = Color::Red;
        }
    )";*/

    TokenMap tokens = extractor.extractAll(headerContent, sourceContent);

    // Afficher les tokens, directives et macros extraits
    for (const auto& [info, type] : tokens) {
        auto [tokenType, file, line, col, original] = info;
        std::cout << "Type: " << type
                  << ", Fichier: " << file
                  << ", Ligne: " << line
                  << ", Colonne: " << col
                  << ", Mot: " << original << "\n";
    }

    return 0;
}
