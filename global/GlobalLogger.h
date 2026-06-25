//
// Created by Sybatron on 6/15/2026.
//

#ifndef MARKDOWNPARSER_GLOBALLOGGER_H
#define MARKDOWNPARSER_GLOBALLOGGER_H
#include <string>
#include <vector>


class GlobalLogger {
private:
    static std::vector<std::string> mErrors;

public:
    /**
    * @brief Форматира и записва съобщение за грешка в глобалния лог.
    *
    * @param line Номерът на реда, в който е открита грешката.
    * @param col Номерът на колоната, където започва проблемът.
    * @param msg Текстово описание на самата грешка или предупреждение.
    *
    * @see mErrors
    */
    static void log(unsigned line, unsigned col, const std::string &msg);

    static bool hasErrors();

    /**
    * @brief Извежда всички записани съобщения за грешки в стандартния поток за грешки (std::cerr).
    *
    * @see mErrors
    * @see log(unsigned, unsigned, const std::string&)
    */
    static void print();

    static void clear();
};


#endif //MARKDOWNPARSER_GLOBALLOGGER_H
