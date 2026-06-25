//
// Created by Sybatron on 6/25/2026.
//

#include "Utility.h"

#include <iostream>

void Utility::debugPrintTree(ASTNode *node, int depth) {
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
