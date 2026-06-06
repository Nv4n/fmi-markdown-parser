//
// Created by Sybatron on 5/16/2026.
//

#include "Tokenizer.h"

#include <stdexcept>

Tokenizer::Tokenizer(const std::string &source) : source(source), position(0) {
}

std::vector<Token> Tokenizer::tokenize(const std::string &source) {
    std::vector<Token> tokens;
    while (position < source.length()) {
        char currentChar = source[position];
        if (isWhitespace(currentChar)) {
            position++;
            continue;
        }
        if (currentChar == '#') {
            position++;
            if (position < source.length() && source[position] != '#') {
                std::string line = source.substr(position);
                position = source.length();
                tokens.push_back({TokenType::HEADER_1, line});
                continue;
            } else {
                tokens.push_back({TokenType::HEADER_2, "#"});
                continue;
            }
        }
        if (currentChar == '*' || currentChar == '-' || currentChar == '.') {
            tokens.push_back({TokenType::LIST_ITEM, source.substr(position)});
            continue;
        }
        if (currentChar == '`') {
            position++;
            if (position < source.length() && source[position] == '`') {
                //TODO DOESN'T CHECK FOR NEXT ONE
                position++;
                tokens.push_back({TokenType::CODE_BLOCK, "```"});
                while (position < source.length() && source[position] != '`') {
                    position++;
                }
                tokens.push_back({TokenType::CODE_BLOCK, "```"});
            } else {
                throw std::runtime_error("Unexpected character");
            }
            continue;
        }
        tokens.push_back({TokenType::TEXT_NODE, std::string(1, currentChar)});
        position++;
    }
    tokens.push_back({TokenType::END_OF_FILE, ""});
    return tokens;
}

bool Tokenizer::isWhitespace(char c) const {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

