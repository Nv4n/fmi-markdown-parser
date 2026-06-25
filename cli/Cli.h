//
// Created by Sybatron on 5/16/2026.
//

#ifndef FMI_MARKDOWN_PARSER_CLI_H
#define FMI_MARKDOWN_PARSER_CLI_H


#include "HtmlWriter.h"
#include "Lexer.h"
#include "MarkdownParser.h"

class Cli {
private:
    MarkdownParser *parser = nullptr;
    Lexer *lexer = nullptr;
    HtmlWriter *htmlWriter = nullptr;
    std::string oldInput;

public:
    Cli();

    Cli(const Cli &) = delete;

    Cli &operator=(const Cli &) = delete;

    ~Cli();

    /**
    * @brief Стартира главния цикъл на командния интерфейс.
    *
    * @details Всяка въведена линия се разделя на аргументи чрез помощния метод
    *          `parseArguments()`, след което се предава за изпълнение на `executeCommand()`.
    *
    * @note Функцията блокира изпълнението на нишката, в която е извикана,
    *       докато потребителят не излезе от програмата.
    *
    * @see parseArguments(const std::string&)
    * @see executeCommand(const std::vector<std::string>&)
    */
    void run();

private:
    /**
    *
    * @param input входен файл .md
    * @param output изходен файл .html
    *
    * @brief Превежда Markdown към HTML. Ако <output> вече съществува,
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
     * @brief Принтира синтактичното дърво на Markdown в подходящ форматиран вид.
     * Дървото трябва да включва всички редове и всички вложени форматиращи елементи. Ако
     * дървото не се събира на един екран, да се поддържа странициране.

     */
    void print(std::string input);


    /**
     *
     * @param input входен файл .md
     *
     * @brief Проверява дали входният файл съдържа валиден Markdown по описания синтаксис. При
     * грешки - извежда списък с редовете и описание на грешката (например незатворен ** блок,
     * неподходящо ниво на #, и т.н.).
     */
    void validate(const std::string &input);

    /**
    * @brief Проверява дали даден низ завършва със специфична наставка.
    *
    * @param str Базовият низ, чийто край се проверява.
    * @param suffix Търсената наставка, с който низът трябва да завършва.
    *
    * @return true Ако базовият низ е по-дълъг или равен на наставката и завършва точно с нея.
    * @return false Ако базовият низ е по-къс от наставакта или не завършва с нея.
    */
    bool endsWith(const std::string &str, const std::string &suffix);

    /**
    * @brief Разделя входния команден низ на вектор от отделни аргументи.
    *
    * @param input Команден низ, въведен от потребителя в конзолата.
    * @return std::vector<std::string> Списък от извлечените аргументи,
    *         където първият елемент обикновено е името на командата.
    *
    * @note Празните интервали извън кавичките се игнорират и не създават празни аргументи.
    *
    * @see run()
    * @see executeCommand(const std::vector<std::string>&)
    */
    std::vector<std::string> parseArguments(const std::string &input);

    /**
    * @brief Разпознава, валидира и изпълнява подадената потребителска команда.
    *
    * @param args Вектор от низове, съдържащ командата (на индекс 0) и нейните аргументи.
    *
    * @see endsWith(const std::string&, const std::string&)
    * @see translate(const std::string&, const std::string&)
    * @see print(const std::string&)
    * @see validate(const std::string&)
    */
    void executeCommand(const std::vector<std::string> &args);
};


#endif //FMI_MARKDOWN_PARSER_CLI_H
