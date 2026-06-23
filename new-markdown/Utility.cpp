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

bool Utility::isDigit(char c) {
    return c >= '0' && c <= '9';
}
