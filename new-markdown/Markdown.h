//
// Created by Sybatron on 6/15/2026.
//

#ifndef MARKDOWNPARSER_MARKDOWN_H
#define MARKDOWNPARSER_MARKDOWN_H
#include <string>
#include <vector>

enum class NodeType {
    ROOT, HEADER, PARAGRAPH,
    UNORDERED_LIST, ORDERED_LIST, LIST_ITEM,
    HORIZONTAL_RULE, CODE_BLOCK,
    BOLD, ITALIC, STRIKETHROUGH, INLINE_CODE, TEXT, SUBSCRIPT
};

struct ASTNode {
    NodeType type;
    std::string content;
    int level; // Used for header levels (1-6)
    std::vector<ASTNode *> children;

    ASTNode(NodeType token, std::string value = "", int level = 0)
        : type(token), content(value), level(level) {
    }


    ~ASTNode() {
        // Move all current children to our local cleanup stack
        std::vector<ASTNode *> stack = std::move(children);

        while (!stack.empty()) {
            // Pop a node off the stack
            ASTNode *current = stack.back();
            stack.pop_back();

            if (current != nullptr) {
                // Transfer current's children to our flat stack before deleting it
                for (ASTNode *child: current->children) {
                    stack.push_back(child);
                }

                // Clear the child's vector so its own destructor does not recurse
                current->children.clear();

                // Safe to delete! It won't trigger a recursive chain.
                delete current;
            }
        }
    }
};

enum class TokenType {
    HASH, STAR, DOUBLE_STAR, DASH, TRIPLE_DASH, TILDE, DOUBLE_TILDE,
    BACKTICK, TRIPLE_BACKTICK, NUMBER, DOT, SPACE, NEWLINE, TEXT, END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
    unsigned line;
    unsigned col;
};


#endif //MARKDOWNPARSER_MARKDOWN_H
