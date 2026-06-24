//
// Created by Sybatron on 6/24/2026.
//

#ifndef MARKDOWNPARSER_HTMLWRITER_H
#define MARKDOWNPARSER_HTMLWRITER_H
#include "Markdown.h"


class HTMLGenerator {
private:
    struct StackAction {
        const ASTNode *node;
        bool isClosing;
    };

public:
    HTMLGenerator() = default;


    bool generate(const ASTNode *root, const std::string &filename);

private:
    std::string escapeHTML(const std::string &data);

    void saveBoilerplate(std::ofstream &outFile);


    bool requiresClosingTag(NodeType type);

    void writeOpeningTagAndContent(const ASTNode *node, std::ofstream &out);

    void writeClosingTag(const ASTNode *node, std::ofstream &out);
};


#endif //MARKDOWNPARSER_HTMLWRITER_H
