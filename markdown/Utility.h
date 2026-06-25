//
// Created by Sybatron on 6/23/2026.
//

#ifndef MARKDOWNPARSER_UTILITY_H
#define MARKDOWNPARSER_UTILITY_H


class Utility {
public:
    /**
    * @brief Проверява дали даден символ поддържа escaping.
    *
    * @param c Символът, който се проверява.
    * @return true Ако символът може да бъде escaping.
    * @return false Ако символът е обикновен знак и не изисква или не поддържа escaping.
    */
    static bool isEscapable(char c);

    /**
    * @brief Проверява дали даден символ е специален знак за лексера.
    *
    * @param c Символът, който се проверява.
    * @return true Ако символът е специален специален знак.
    * @return false Ако символът е стандартен текст, число или друг знак.
    */
    static bool isSpecial(char c);

    static bool isDigit(char c);
};


#endif //MARKDOWNPARSER_UTILITY_H
