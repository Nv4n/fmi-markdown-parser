//
// Created by Sybatron on 6/15/2026.
//

#ifndef MARKDOWNPARSER_PARSER_H
#define MARKDOWNPARSER_PARSER_H


#include <vector>

#include "Markdown.h"
#include "GlobalLogger.h"

class MarkdownParser {
private:
    std::vector<Token> memTokens;
    GlobalLogger &memLogger;
    size_t memCursor = 0;

    Token peek();

    Token advance();

    bool isEOF();

    // Helper function to extract a single line of empty / new line tokens for structural analysis
    std::vector<Token> consumeLine();

    // Inline processing logic using explicit tracking states
    void parseInlineContent(const std::vector<Token> &tokens, ASTNode *parent);

public:
    MarkdownParser(const std::vector<Token> &tokens, GlobalLogger &logger);

    ASTNode *parse();
};


#endif //MARKDOWNPARSER_PARSER_H
