//
// Created by Sybatron on 6/25/2026.
//

#ifndef MARKDOWNPARSER_UTILITY_H
#define MARKDOWNPARSER_UTILITY_H
#include "Markdown.h"


class Utility {
public:
    /**
    * @brief Принтира рекурсивно структурата на Abstract Syntax Tree (AST) в конзолата за дебъгване.
    *
    * Функция обхожда дървото в дълбочина (DFS) и визуализира типа на всеки Node,
    * като добавя индентация спрямо текущото ниво на вложеност (depth).
    *
    * @param node Указател към коренния Node (ASTNode) на дървото или поддървото, което ще се принтира.
    * @param depth Текущото ниво на индентация в дървото (използва се за форматиране на отстъпите).
    *
    * @note Функцията извежда информацията директно в стандартния изход (`std::cout`).
    *
    * @warning Ако структурата на дървото съдържа циклични референции между възлите,
    *          функцията ще влезе в безкрайна рекурсия и ще предизвика Stack Overflow.
    */
    static void debugPrintTree(ASTNode *node, int depth = 0);
};


#endif //MARKDOWNPARSER_UTILITY_H
