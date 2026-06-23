//
// Created by Sybatron on 5/16/2026.
//

#ifndef FMI_MARKDOWN_PARSER_CLI_H
#define FMI_MARKDOWN_PARSER_CLI_H
#include "Lexer.h"
#include "Parser.h"


class Cli {
private:
    MarkdownParser *parser = nullptr;
    Lexer *lexer = nullptr;
    std::string oldInput;

public:
    Cli();

    Cli(const Cli &) = delete;

    Cli &operator=(const Cli &) = delete;

    ~Cli();

    void run();

private:
    /**
     *
     * @param input входен файл .md
     * @param output изходен файл .html
     *
    * Превежда Markdown към HTML. Ако <output> вече съществува,
    * потребителят трябва да бъде попитан за потвърждение преди презаписване.
    *
    * Output: Резултат от операцията. При грешки (несъществуващ входен файл, невалиден
    * синтаксис, проблеми при запис) - подходящо съобщение.

     */
    void translate(std::string input, std::string output);

    /**
     *
     * @param input - входен файл .md
     *
     * Принтира синтактичното дърво на Markdown в подходящ форматиран вид.
     * Дървото трябва да включва всички редове и всички вложени форматиращи елементи. Ако
     * дървото не се събира на един екран, да се поддържа странициране.

     */
    void print(std::string input);


    /**
     *
     * @param input входен файл .md
     *
     * Проверява дали входният файл съдържа валиден Markdown по описания синтаксис. При
     * грешки - извежда списък с редовете и описание на грешката (например незатворен ** блок,
     * неподходящо ниво на #, и т.н.).
     */
    void validate(std::string input);
};


#endif //FMI_MARKDOWN_PARSER_CLI_H
