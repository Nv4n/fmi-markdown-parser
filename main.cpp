#include <iostream>

#include <sstream>

#include "Cli.h"
#include "Markdown.h"
#include "GlobalLogger.h"
#include "html/HtmlWriter.h"
#include "markdown/Lexer.h"
#include "markdown/MarkdownParser.h"

// Helper structure to recursively trace our tree format
void debugPrintTree(ASTNode *node, int depth = 0) {
    std::string indent(depth * 2, ' ');
    std::cout << indent;

    switch (node->type) {
        case NodeType::ROOT: std::cout << "[Document Root]\n";
            break;
        case NodeType::HEADER: std::cout << "[H" << node->level << "]\n";
            break;
        case NodeType::PARAGRAPH: std::cout << "[Paragraph]\n";
            break;
        case NodeType::UNORDERED_LIST: std::cout << "[Unordered List]\n";
            break;
        case NodeType::ORDERED_LIST: std::cout << "[Ordered List]\n";
            break;
        case NodeType::LIST_ITEM: std::cout << "[List Item " << node->content << "]\n";
            break;
        case NodeType::HORIZONTAL_RULE: std::cout << "[Horizontal Rule (---)]\n";
            break;
        case NodeType::CODE_BLOCK: std::cout << "[Code Block Content:\n" << node->content << "]\n";
            break;
        case NodeType::BOLD: std::cout << "<Bold>\n";
            break;
        case NodeType::ITALIC: std::cout << "<Italic>\n";
            break;
        case NodeType::STRIKETHROUGH: std::cout << "<Strikethrough>\n";
            break;
        case NodeType::SUBSCRIPT: std::cout << "<sub>" << "\n";
            break;
        case NodeType::INLINE_CODE: std::cout << "<code> (" << node->content << ")\n";
            break;
        case NodeType::TEXT: std::cout << "Text: \"" << node->content << "\"\n";
            break;
    }

    for (auto child: node->children) {
        debugPrintTree(child, depth + 1);
    }
}

void demo() {
    // Construct sample markdown demonstrating every requested feature
    std::stringstream markdownSource;
    markdownSource << "# Header Level 1\n"
            << "### ***Header*** *Level* 3\n"
            << "---\n"
            << "This is a normal paragraph showing **bold text**, *italics*, and ~~strikethrough styles~~.\n"
            << "You can also include `inline code units` safely inside paragraphs.\n\n"
            << "- Unordered *Item* 1\n"
            << "- Unordered Item 2 with **bold formatting**\n\n"
            << "1. First ordered branch\n"
            << "2. Second ordered branch\n\n"
            << "```\n"
            << "void main() {\n"
            << "    int value = 42;\n"
            << "}\n"
            << "```\n"
            << "Ending block text with mismatched **bold flag check.";

    Lexer lexer(markdownSource);
    std::vector<Token> tokens = lexer.tokenize2();

    MarkdownParser parser(tokens);
    bool didBreak = false;
    ASTNode *treeRoot = nullptr;
    try {
        treeRoot = parser.parse();
        std::cout << "--- COMPILER TREE RESULT ---\n";
        debugPrintTree(treeRoot);
    } catch (std::exception &e) {
        didBreak = true;
        delete treeRoot;
        GlobalLogger::log(0, 0, "AST tree couldn't be parsed");
    } catch (...) {
        didBreak = true;
        delete treeRoot;
    }


    std::cout << "\n--- ERROR LOGGER LOGS ---\n";
    if (GlobalLogger::hasErrors()) {
        GlobalLogger::print();
    } else {
        std::cout << "All clear! No errors registered during evaluation.\n";
    }

    HtmlWriter htmlGenerator;
    htmlGenerator.save(treeRoot, "index.html");
    // Clean up memory
    if (!didBreak && treeRoot != nullptr) {
        delete treeRoot;
    }
}

int main() {
    // demo();
    Cli cli;
    cli.run();
}
