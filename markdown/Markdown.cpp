//
// Created by Sybatron on 6/15/2026.
//

#include "Markdown.h"

ASTNode::ASTNode(NodeType token, std::string value, int level)
    : type(token), content(value), level(level) {
}

ASTNode::~ASTNode() {
    std::vector<ASTNode *> stack = std::move(children);

    while (!stack.empty()) {
        ASTNode *current = stack.back();
        stack.pop_back();

        if (current != nullptr) {
            for (ASTNode *child: current->children) {
                stack.push_back(child);
            }
            current->children.clear();

            delete current;
        }
    }
}
