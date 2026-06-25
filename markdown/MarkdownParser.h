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
    std::vector<Token> mTokens;
    size_t mCursor = 0;

public:
    MarkdownParser(const std::vector<Token> &tokens);

    ~MarkdownParser() = default;

    ASTNode *parse();

private:
    Token peek();

    /**
    * @brief Консумира текущия токен и придвижва курсора напред с една позиция.
    *
    * @return Token Токенът, който е бил на текущата позиция преди инкрементирането.
    *
    * @warning Този метод не извършва проверка за препълване на границите на вектора (bounds checking).
    *          Преди извикване се уверете, че курсорът не е достигнал края на `mTokens`.
    *
    * @see mCursor
    * @see mTokens
    */
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

    /**
    * @brief Парсва вътрешните Markdown елементи от списък с токени.
    *
    * @param tokens Вектор от токени, съдържащ съдържанието на текущия ред или блок.
    * @param parent Указател към родителския AST Node
    *
    * @note При несъответствие или липса на затварящ маркер (delimiter), методът
    *       `handleInlineElement()` обработва текста по подразбиране като обикновен текст,
    *       като за някои формати извежда предупредително съобщение.
    *
    * @see Token
    * @see ASTNode
    * @see handleInlineElement(const std::vector<Token>&, unsigned, ASTNode*, TokenType, NodeType, const std::string&)
    */
    void parseInlineContent(const std::vector<Token> &tokens, ASTNode *parent);

    /**
    * @brief Обработва специфичен вътрешен елемент, като търси неговия затварящ маркер.
    *
    * @param tokens Вектор от токени, в който се извършва търсенето.
    * @param ind Текущият индекс на отварящия токен във вектора.
    * @param parent Указател към родителския AST Node, към който ще се добави новият елемент.
    * @param targetType Типът на токена, който се явява затварящ маркер (delimiter).
    * @param nodeType Типът на AST Node, който трябва да се създаде при успешно съответствие.
    * @param errorMsg Предупредително съобщение, което да се логне, ако затварящият маркер липсва.
    *
    * @return unsigned Новият индекс във вектора с токени, от който парсерът трябва да продължи работа.
    *
    * @see GlobalLogger::log(int, int, const std::string&)
    * @see parseInlineContent(const std::vector<Token>&, ASTNode*)
    */
    unsigned handleInlineElement(const std::vector<Token> &tokens, unsigned ind, ASTNode *parent,
                                 TokenType targetType, NodeType nodeType, const std::string &errorMsg);
};


#endif //MARKDOWNPARSER_PARSER_H
