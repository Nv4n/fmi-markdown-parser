//
// Created by Sybatron on 6/15/2026.
//

#ifndef MARKDOWNPARSER_MARKDOWN_H
#define MARKDOWNPARSER_MARKDOWN_H
#include <string>
#include <vector>

enum class NodeType {
    ROOT, HEADER, PARAGRAPH,
    UNORDERED_LIST, ORDERED_LIST, LIST_ITEM,
    HORIZONTAL_RULE, CODE_BLOCK,
    BOLD, ITALIC, STRIKETHROUGH, INLINE_CODE, TEXT, SUBSCRIPT
};

struct ASTNode {
    NodeType type;
    std::string content;
    int level; // Used for header levels (1-6)
    std::vector<ASTNode *> children;

    ASTNode(NodeType token, std::string value = "", int level = 0);

    ~ASTNode();
};

enum class TokenType {
    HASH, STAR, DOUBLE_STAR, DASH, TRIPLE_DASH, TILDE, DOUBLE_TILDE,
    BACKTICK, TRIPLE_BACKTICK, NUMBER, DOT, SPACE, NEWLINE, TEXT, END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
    unsigned line;
    unsigned col;
};


#endif //MARKDOWNPARSER_MARKDOWN_H
