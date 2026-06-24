//
// Created by Sybatron on 6/24/2026.
//

#include "HtmlWriter.h"
#include "GlobalLogger.h"

#include <fstream>


bool HTMLGenerator::generate(const ASTNode *root, const std::string &filename) {
    if (!root) return false;

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        GlobalLogger::log(0, 0, "Error: Could not open file " + filename + " for writing.");
        return false;
    }
    //     <!DOCTYPE html>
    // <html lang="en">
    // <head>
    //     <meta charset="UTF-8">
    //     <meta name="viewport" content="width=device-width, initial-scale=1.0">
    //     <title>Document</title>
    // </head>
    // <body>
    //
    // </body>
    // </html>
    saveBoilerplate(outFile);

    // Iterative Stack Traversal
    std::vector<StackAction> stack;

    // Initialize stack with the root node
    stack.push_back({root, false});

    while (!stack.empty()) {
        StackAction current = stack.back();
        stack.pop_back();

        if (!current.node) continue;

        if (current.isClosing) {
            // Handle closing tags when we backtrack up the tree
            writeClosingTag(current.node, outFile);
        } else {
            // Handle opening tags and content
            writeOpeningTagAndContent(current.node, outFile);

            // If this node has children, we need to schedule its closing tag,
            // and then schedule its children to be processed.
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

void HTMLGenerator::saveBoilerplate(std::ofstream &outFile) {
    outFile << "<!DOCTYPE html>\n"
            << "<html lang=\"en\">\n"
            << "<head>\n"
            << "    <meta charset=\"UTF-8\">\n"
            << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
            << "    <title>Document</title>\n"
            << "</head>\n"
            << "<body>" << std::endl;
}


std::string HTMLGenerator::escapeHTML(const std::string &data) {
    std::string buffer;
    buffer.reserve(data.size());
    for (size_t pos = 0; pos != data.size(); ++pos) {
        switch (data[pos]) {
            case '&': buffer.append("&amp;");
                break;
            case '\"': buffer.append("&quot;");
                break;
            case '\'': buffer.append("&apos;");
                break;
            case '<': buffer.append("&lt;");
                break;
            case '>': buffer.append("&gt;");
                break;
            default: buffer.append(&data[pos], 1);
                break;
        }
    }
    return buffer;
}

bool HTMLGenerator::requiresClosingTag(NodeType type) {
    return !(type == NodeType::TEXT || type == NodeType::HORIZONTAL_RULE || type == NodeType::INLINE_CODE);
}

void HTMLGenerator::writeOpeningTagAndContent(const ASTNode *node, std::ofstream &out) {
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

void HTMLGenerator::writeClosingTag(const ASTNode *node, std::ofstream &out) {
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

