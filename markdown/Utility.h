//
// Created by Sybatron on 6/23/2026.
//

#ifndef MARKDOWNPARSER_UTILITY_H
#define MARKDOWNPARSER_UTILITY_H


class Utility {
public:
    static bool isEscapable(char c);

    static bool isSpecial(char c);

    static bool isDigit(char c);
};


#endif //MARKDOWNPARSER_UTILITY_H
