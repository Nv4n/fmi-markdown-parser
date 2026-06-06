//
// Created by Sybatron on 5/16/2026.
//

#ifndef FMI_MARKDOWN_PARSER_TOKENIZER_H
#define FMI_MARKDOWN_PARSER_TOKENIZER_H
#include <string>
#include <vector>

enum class TokenType {
    HEADER_1,
    HEADER_2,
    HEADER_3,
    HEADER_4,
    HEADER_5,
    HEADER_6,
    PARAGRAPH,
    CODE_BLOCK,
    UNORDERED_LIST,
    ORDERED_LIST,
    LIST_ITEM,
    BOLD,
    ITALIC,
    STRIKETHROUGH,
    HORIZONTAL_LINE,
    TEXT_NODE,
    END_OF_FILE
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
};

class Tokenizer {
private:
    std::string source;
    unsigned position = 0;

public:
    Tokenizer(const std::string &source);

    std::vector<Token> tokenize(const std::string &source);

private:
    bool isWhitespace(char c) const;
};


#endif //FMI_MARKDOWN_PARSER_TOKENIZER_H
