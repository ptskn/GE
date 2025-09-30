//
// Created by ptskn on 16/09/2025.
//

#ifndef SAASCORE_CLANGTOKENSEXTRACTOR_H
#define SAASCORE_CLANGTOKENSEXTRACTOR_H
#include <clang-c/Index.h>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>

// Types pour les tokens et les résultats
using TokenInfo = std::tuple<std::string, std::string, int, int, std::string>;
using TokenMap = std::map<TokenInfo, std::string>; // Type détaillé en valeur

class ClangTokensExtractor {
public:
    ClangTokensExtractor() : index(clang_createIndex(0, 0)) {}

    ~ClangTokensExtractor() {
        clang_disposeIndex(index);
    }

    // Extrait tous les tokens, directives et macros
    TokenMap extractAll(const std::string& headerContent, const std::string& sourceContent) {
        TokenMap tokens;

        // Écrire les contenus dans des fichiers temporaires
        std::string headerPath = "temp_header.h";
        std::string sourcePath = "temp_source.cpp";
        writeToFile(headerPath, headerContent);
        writeToFile(sourcePath, sourceContent);

        // Analyser chaque fichier
        extractTokensFromFile(headerPath, tokens);
        extractTokensFromFile(sourcePath, tokens);

        // Nettoyer les fichiers temporaires
        remove(headerPath.c_str());
        remove(sourcePath.c_str());

        return tokens;
    }

private:
    CXIndex index;

    void writeToFile(const std::string& path, const std::string& content) {
        FILE* file = fopen(path.c_str(), "w");
        if (!file) {
            throw std::runtime_error("Impossible d'écrire le fichier temporaire.");
        }
        fwrite(content.c_str(), 1, content.size(), file);
        fclose(file);
    }

    // Extrait les tokens, directives et macros d'un fichier
    void extractTokensFromFile(const std::string& filePath, TokenMap& tokens) {
        const char* args[] = {"-E", "-I."};
        CXTranslationUnit unit = clang_parseTranslationUnit(
            index, filePath.c_str(), args, 2, nullptr, 0, CXTranslationUnit_None);

        if (!unit) {
            std::cerr << "Erreur lors de l'analyse de " << filePath << "\n";
            return;
        }

        // Récupérer le fichier
        CXFile file = clang_getFile(unit, filePath.c_str());
        if (!file) {
            std::cerr << "Fichier non trouvé dans l'unité de traduction.\n";
            clang_disposeTranslationUnit(unit);
            return;
        }

        // Tokenizer le fichier
        CXToken* clangTokens;
        unsigned numTokens;
        CXSourceRange range = clang_getRange(
            clang_getLocation(unit, file, 1, 1),
            clang_getLocation(unit, file, UINT_MAX, UINT_MAX)
        );
        clang_tokenize(unit, range, &clangTokens, &numTokens);

        // Extraire les tokens classiques
        for (unsigned i = 0; i < numTokens; ++i) {
            CXTokenKind kind = clang_getTokenKind(clangTokens[i]);
            CXString spelling = clang_getTokenSpelling(unit, clangTokens[i]);
            CXSourceLocation loc = clang_getTokenLocation(unit, clangTokens[i]);
            unsigned line, column;
            clang_getFileLocation(loc, nullptr, &line, &column);

            std::string tokenStr = clang_getCString(spelling);
            std::string typeStr = getTokenTypeString(kind);

            // Ajouter à la map avec le type détaillé
            TokenInfo info = std::make_tuple(
                typeStr, filePath, line, column, tokenStr);
            tokens[info] = typeStr;

            clang_disposeString(spelling);
        }

        // Extraire les directives préprocesseur
        extractPreprocessorDirectives(unit, filePath, tokens);

        // Extraire les macros
        extractMacros(unit, filePath, tokens);

        clang_disposeTokens(unit, clangTokens, numTokens);
        clang_disposeTranslationUnit(unit);
    }

    // Extrait les directives préprocesseur
    void extractPreprocessorDirectives(CXTranslationUnit unit, const std::string& filePath, TokenMap& tokens) {
        unsigned numDiags = clang_getNumDiagnostics(unit);
        for (unsigned i = 0; i < numDiags; ++i) {
            CXDiagnostic diag = clang_getDiagnostic(unit, i);
            CXSourceLocation loc = clang_getDiagnosticLocation(diag);
            CXString diagStr = clang_getDiagnosticSpelling(diag);
            std::string diagMsg = clang_getCString(diagStr);

            if (diagMsg.find("#") != std::string::npos) {
                unsigned line, column;
                CXFile file;
                clang_getFileLocation(loc, &file, &line, &column);
                CXString fileName = clang_getFileName(file);
                std::string filePathStr = clang_getCString(fileName);

                // Ajouter à la map avec le type "directive"
                TokenInfo info = std::make_tuple(
                    "directive", filePathStr, line, column, diagMsg);
                tokens[info] = "directive";

                clang_disposeString(fileName);
            }

            clang_disposeString(diagStr);
            clang_disposeDiagnostic(diag);
        }
    }

    // Extrait les macros et leurs définitions
    void extractMacros(CXTranslationUnit unit, const std::string& filePath, TokenMap& tokens) {
        // Récupérer le curseur de l'unité de traduction
        CXTUResourceUsage usage;
        clang_getCXTUResourceUsage(unit, &usage);

        // Parcourir les macros définies
        for (unsigned i = 0; i < usage.numMacros; ++i) {
            CXString macroName = clang_getCXTUResourceUsageMacroName(usage, i);
            CXString macroDef = clang_getCXTUResourceUsageMacroDefinition(usage, i);
            std::string name = clang_getCString(macroName);
            std::string def = clang_getCString(macroDef);

            // Trouver la localisation de la macro (simplifié ici)
            // En pratique, il faudrait utiliser clang_getCursor pour localiser la macro
            // Ici, on suppose que la macro est définie dans le fichier courant
            unsigned line = 1, column = 1; // À améliorer

            // Ajouter à la map avec le type "macro"
            TokenInfo info = std::make_tuple(
                "macro", filePath, line, column, name + " -> " + def);
            tokens[info] = "macro";

            clang_disposeString(macroName);
            clang_disposeString(macroDef);
        }
    }

    // Retourne le type de token sous forme de chaîne
    std::string getTokenTypeString(CXTokenKind kind) {
        switch (kind) {
            case CXToken_Punctuation: return "punctuation";
            case CXToken_Keyword: return "keyword";
            case CXToken_Identifier: return "identifier";
            case CXToken_Literal: return "literal";
            case CXToken_Comment: return "comment";
            default: return "unknown";
        }
    }
};

#endif //SAASCORE_CLANGTOKENSEXTRACTOR_H