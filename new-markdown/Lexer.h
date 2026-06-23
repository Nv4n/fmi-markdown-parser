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

    /**
     * @brief Прочита следващия символ от входния поток и обновява позицията (ред и колона).
    * @return char Прочетеният символ от потока.
    */
    char getChar();

    /**
    * @return char Следващият символ в потока или `std::char_traits<char>::eof()`,
    * ако е достигнат краят на файла.
    */
    char peekChar() const;

public:
    Lexer(std::istream &input);

    std::vector<Token> tokenize();
};

#endif //MARKDOWNPARSER_LEXER_H
