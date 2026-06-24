//
// Created by Sybatron on 6/15/2026.
//

#ifndef MARKDOWNPARSER_LEXER_H
#define MARKDOWNPARSER_LEXER_H


#include <istream>
#include "Markdown.h"

#include "GlobalLogger.h"

class Lexer {
private:
    std::istream &memInput;

    unsigned mLine = 1;
    unsigned mCol = 0;
    unsigned starCount = 0;
    bool isTripleStar = false;

    /**
    * @brief Прочита следващия символ от входния поток и обновява позицията (ред и колона).
    * @return char Прочетеният символ от потока.
    *
    * @note TODO might fail reading
    */
    char getChar();

    /**
    * @return char Следващият символ в потока или `std::char_traits<char>::eof()`,
    * ако е достигнат краят на файла.
    *
    */
    char peekChar() const;

public:
    Lexer(std::istream &input);

    std::vector<Token> tokenize();

    std::vector<Token> tokenize2();

private:
    void handleBackslash(std::vector<Token> &tokens);

    void handleNewline(std::vector<Token> &tokens);

    void handleSpace(std::vector<Token> &tokens);

    void handleHash(std::vector<Token> &tokens);

    void handleStar(std::vector<Token> &tokens);

    void handleDash(std::vector<Token> &tokens);

    void handleTilde(std::vector<Token> &tokens);

    void handleBacktick(std::vector<Token> &tokens);

    void handleDot(std::vector<Token> &tokens);

    void handleNumber(std::vector<Token> &tokens);

    void handleText(std::vector<Token> &tokens);
};

#endif //MARKDOWNPARSER_LEXER_H
