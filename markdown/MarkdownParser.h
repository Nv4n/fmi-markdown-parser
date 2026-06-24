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
    size_t memCursor = 0;

    Token peek();

    Token advance();

    bool isEOF();

    /**
     * @brief Помощна функция за извличане на един ред от токени.
     *
     * Методът обхожда и събира всички токени до достигане на края на файла (EOF)
     * или до срещането на токен за нов ред (TokenType::NEWLINE).
     *
     * @return std::vector<Token> Списък с всички токени, съдържащи се в текущия ред.
     */
    std::vector<Token> consumeLine();

    void parseInlineContent(const std::vector<Token> &tokens, ASTNode *parent);

    unsigned handleInlineElement(const std::vector<Token> &tokens, unsigned ind, ASTNode *parent,
                                 TokenType targetType, NodeType nodeType, const std::string &errorMsg);

public:
    MarkdownParser(const std::vector<Token> &tokens);

    ~MarkdownParser() = default;

    ASTNode *parse();
};


#endif //MARKDOWNPARSER_PARSER_H
