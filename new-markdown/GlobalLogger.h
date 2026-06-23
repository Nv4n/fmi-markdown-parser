//
// Created by Sybatron on 6/15/2026.
//

#ifndef MARKDOWNPARSER_GLOBALLOGGER_H
#define MARKDOWNPARSER_GLOBALLOGGER_H
#include <iostream>
#include <string>
#include <vector>


class GlobalLogger {
private:
    static std::vector<std::string> mErrors;

public:
    static void log(unsigned line, unsigned col, const std::string &msg);

    static bool hasErrors();

    static void print();

    static void clear();
};


#endif //MARKDOWNPARSER_GLOBALLOGGER_H
