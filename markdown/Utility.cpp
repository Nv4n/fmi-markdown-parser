//
// Created by Sybatron on 6/23/2026.
//

#include "Utility.h"

bool Utility::isEscapable(char c) {
    return c == '\\' || c == '_' ||
           c == '{' || c == '}' || c == '[' || c == ']' ||
           c == '(' || c == ')' || c == '+' ||
           c == '!' || c == '#' || c == '`' || c == '*' || c == '-' || c == '.';
}

bool Utility::isSpecial(char c) {
    return c == '#' || c == '`' || c == '*' || c == '-' || c == '~';
}

/**
 * @brief Проверява дали даден символ е ASCII цифра.
 *
 * @param c Символът, който се проверява.
 * @return true Ако символът е цифра (от '0' до '9').
 * @return false Ако символът е друг символ.
 */
bool Utility::isDigit(char c) {
    return c >= '0' && c <= '9';
}
