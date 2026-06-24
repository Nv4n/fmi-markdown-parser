//
// Created by Sybatron on 6/24/2026.
//

#include "HtmlWriter.h"
#include "GlobalLogger.h"

#include <fstream>


bool HtmlWriter::save(const ASTNode *root, const std::string &filename) {
    if (!root) return false;

    std::ofstream outFile(std::string(SUBDIR_ASSET_PATH) + filename);
    if (!outFile.is_open()) {
        GlobalLogger::log(0, 0, "Error: Could not open file " + filename + " for writing.");
        return false;
    }
    saveBoilerplate(outFile);

    std::vector<StackAction> stack;

    stack.push_back({root, false});

    while (!stack.empty()) {
        StackAction current = stack.back();
        stack.pop_back();

        if (!current.node) continue;

        if (current.isClosing) {
            writeClosingTag(current.node, outFile);
        } else {
            writeOpeningTagAndContent(current.node, outFile);
            if (!current.node->children.empty() && requiresClosingTag(current.node->type)) {
                // 1. Push closing action first (so it executes last)
                stack.push_back({current.node, true});

                // 2. Push children in REVERSE order so they are processed left-to-right
                for (auto it = current.node->children.rbegin(); it != current.node->children.rend(); ++it) {
                    stack.push_back({*it, false});
                }
            }
        }
    }

    // Close boilerplate tags
    outFile << "\n</body>\n</html>\n";
    outFile.close();
    return true;
}

void HtmlWriter::saveBoilerplate(std::ofstream &outFile) {
    outFile << "<!DOCTYPE html>\n"
            << "<html lang=\"en\">\n"
            << "<head>\n"
            << "    <meta charset=\"UTF-8\">\n"
            << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
            << "    <title>Document</title>\n"
            << "</head>\n"
            << "<body>" << std::endl;
}


std::string HtmlWriter::escapeHTML(const std::string &data) {
    std::string buffer;
    for (const char &pos: data) {
        switch (pos) {
            case '&': buffer += "&amp;";
                break;
            case '\"': buffer += "&quot;";
                break;
            case '\'': buffer += "&apos;";
                break;
            case '<': buffer += "&lt;";
                break;
            case '>': buffer += "&gt;";
                break;
            default: buffer += pos;
                break;
        }
    }
    return buffer;
}

bool HtmlWriter::requiresClosingTag(NodeType type) {
    return !(type == NodeType::TEXT || type == NodeType::HORIZONTAL_RULE || type == NodeType::INLINE_CODE);
}

void HtmlWriter::writeOpeningTagAndContent(const ASTNode *node, std::ofstream &out) {
    switch (node->type) {
        case NodeType::ROOT: break;
        case NodeType::HEADER: {
            int lvl = (node->level < 1 || node->level > 6) ? 1 : node->level;
            out << "<h" << lvl << ">";
            break;
        }
        case NodeType::PARAGRAPH: out << "<p>";
            break;
        case NodeType::UNORDERED_LIST: out << "<ul>\n";
            break;
        case NodeType::ORDERED_LIST: out << "<ol>\n";
            break;
        case NodeType::LIST_ITEM: out << "<li>";
            break;
        case NodeType::HORIZONTAL_RULE: out << "<hr />\n";
            break;
        case NodeType::CODE_BLOCK: out << "<pre><code>" << escapeHTML(node->content);
            break;
        case NodeType::BOLD: out << "<strong>";
            break;
        case NodeType::ITALIC: out << "<em>";
            break;
        case NodeType::STRIKETHROUGH: out << "<del>";
            break;
        case NodeType::SUBSCRIPT: out << "<sub>";
            break;
        case NodeType::INLINE_CODE: out << "<code>" << escapeHTML(node->content) << "</code>";
            break;
        case NodeType::TEXT: out << escapeHTML(node->content);
            break;
    }
}

void HtmlWriter::writeClosingTag(const ASTNode *node, std::ofstream &out) {
    switch (node->type) {
        case NodeType::ROOT: break;
        case NodeType::HEADER: {
            int lvl = (node->level < 1 || node->level > 6) ? 1 : node->level;
            out << "</h" << lvl << ">\n";
            break;
        }
        case NodeType::PARAGRAPH: out << "</p>\n";
            break;
        case NodeType::UNORDERED_LIST: out << "</ul>\n";
            break;
        case NodeType::ORDERED_LIST: out << "</ol>\n";
            break;
        case NodeType::LIST_ITEM: out << "</li>\n";
            break;
        case NodeType::CODE_BLOCK: out << "</code></pre>\n";
            break;
        case NodeType::BOLD: out << "</strong>";
            break;
        case NodeType::ITALIC: out << "</em>";
            break;
        case NodeType::STRIKETHROUGH: out << "</del>";
            break;
        case NodeType::SUBSCRIPT: out << "</sub>";
            break;
        default: break;
    }
}

