//
// Created by Sybatron on 6/24/2026.
//

#ifndef MARKDOWNPARSER_HTMLWRITER_H
#define MARKDOWNPARSER_HTMLWRITER_H
#include "Markdown.h"


class HtmlWriter {
private:
    struct StackAction {
        const ASTNode *node;
        bool isClosing;
    };

public:
    HtmlWriter() = default;

    /**
    * @brief Записва AST дървото в готов HTML файл, използвайки итеративно обхождане (DFS).
    *
    * @details Алгоритъмът работи по следния начин за всеки Node:
    * - При първо посещение (отваряне) се извиква `writeOpeningTagAndContent()`.
    * - Децата на Node-а се вкарват в стека в обратен ред, за да се обработят коректно от ляво на дясно.
    * - Ако Node-ът изисква затварящ таг, в стека се поставя флаг за затваряне (`isClosing = true`),
    *   което се изпълнява след обработката на всички негови наследници.
    *
    * @param root Указател към коренния Node-ът на AST дървото, което ще се записва.
    * @param filename Името на изходния HTML файл (без пътя, тъй като той се добавя автоматично).
    *
    * @return true Ако файлът е генериран и записан успешно.
    * @return false Ако коренът е невалиден (`nullptr`) или файлът не може да бъде отворен за запис.
    *
    * @note Методът автоматично добавя стандартния HTML5 шаблон в началото (`saveBoilerplate`)
    *       и затваря `</body>` и `</html>` таговете в края на файла преди неговото затваряне.
    *
    * @see StackAction
    * @see saveBoilerplate(std::ofstream&)
    * @see writeOpeningTagAndContent(const ASTNode*, std::ofstream&)
    * @see writeClosingTag(const ASTNode*, std::ofstream&)
    * @see requiresClosingTag(NodeType)
    * @see GlobalLogger::log(int, int, const std::string&)
    */
    bool save(const ASTNode *root, const std::string &filename);

private:
    /**
    * @brief Escape-ва специални символи в низ, за да бъде той безопасен за HTML извеждане.
    *
    * @param data Входният низ, който съдържа неформатиран текст за обработка.
    * @return std::string Новият обработен низ, в който специалните символи са заменени.
    */
    std::string escapeHTML(const std::string &data);

    /**
    * @brief Записва началния стандартен HTML5 шаблон.
    *
    * @param outFile Референция към отворения файлов поток (`std::ofstream`),
    *                в който се записва HTML съдържанието.
    *
    * @warning Потокът `outFile` трябва да бъде предварително успешно отворен
    *          преди подаването му на тази функция.
    */
    void saveBoilerplate(std::ofstream &outFile);

    /**
    * @brief Проверява дали даден тип AST Node изисква затварящ HTML таг.
    *
    * @param type Типът на AST Node.
    * @return true Ако AST Node изисква съответстващ затварящ HTML таг.
    * @return false Ако AST Node не се затварят самостоятелно на това ниво.
    *
    * @see NodeType
    */
    bool requiresClosingTag(NodeType type);

    /**
    * @brief Записва отварящия HTML таг и съдържанието на даден AST Node в изходния поток.
    *
    * @param node Указател към AST Node
    * @param out Референция към изходния файлов поток (`std::ofstream`)
    *
    * @note При заглавия (`NodeType::HEADER`), методът автоматично ограничава нивото (`node->level`)
    *       в рамките на валидния HTML диапазон от 1 до 6. При невалидна стойност се използва `<h2>` по подразбиране.
    *
    * @see ASTNode
    * @see escapeHTML(const std::string&)
    * @see writeClosingTag(const ASTNode*, std::ofstream&)
    */
    void writeOpeningTagAndContent(const ASTNode *node, std::ofstream &out);

    /**
    * @brief Записва съответстващия затварящ HTML таг за даден AST Node.
    *
    * @param node Указател към AST Node
    * @param out Референция към изходния файлов поток (`std::ofstream`)
    *
    * @note Подобно на отварящия таг, нивото на заглавията (`NodeType::HEADER`) се валидира автоматично
    *       в диапазона от 1 до 6, за да се гарантира съответствие и валиден HTML синтаксис.
    *
    * @see ASTNode
    * @see writeOpeningTagAndContent(const ASTNode*, std::ofstream&)
    * @see requiresClosingTag(NodeType)
    */
    void writeClosingTag(const ASTNode *node, std::ofstream &out);
};


#endif //MARKDOWNPARSER_HTMLWRITER_H
