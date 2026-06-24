//
// Created by Sybatron on 6/15/2026.
//

#include "MarkdownParser.h"

Token MarkdownParser::peek() { return memTokens[memCursor]; }

Token MarkdownParser::advance() { return memTokens[memCursor++]; }

bool MarkdownParser::isEOF() { return peek().type == TokenType::END_OF_FILE; }

std::vector<Token> MarkdownParser::consumeLine() {
    std::vector<Token> lineTokens;
    while (!isEOF() && peek().type != TokenType::NEWLINE) {
        lineTokens.push_back(advance());
    }
    if (peek().type == TokenType::NEWLINE) advance();
    return lineTokens;
}

void MarkdownParser::parseInlineContent(const std::vector<Token> &tokens, ASTNode *parent) {
    unsigned ind = 0;
    while (ind < tokens.size()) {
        Token tok = tokens[ind];

        if (tok.type == TokenType::DOUBLE_STAR) {
            ind = handleInlineElement(tokens, ind, parent, TokenType::DOUBLE_STAR, NodeType::BOLD,
                                      "Mismatched Bold delimiters (**). Treated as plain text.");
        } else if (tok.type == TokenType::STAR) {
            ind = handleInlineElement(tokens, ind, parent, TokenType::STAR, NodeType::ITALIC, "");
        } else if (tok.type == TokenType::DOUBLE_TILDE) {
            ind = handleInlineElement(tokens, ind, parent, TokenType::DOUBLE_TILDE, NodeType::STRIKETHROUGH,
                                      "Mismatched Strikethrough delimiters (~~).");
        } else if (tok.type == TokenType::TILDE) {
            ind = handleInlineElement(tokens, ind, parent, TokenType::TILDE, NodeType::SUBSCRIPT,
                                      "Mismatched Subscript delimiters (~).");
        } else if (tok.type == TokenType::BACKTICK) {
            ind = handleInlineElement(tokens, ind, parent, TokenType::BACKTICK, NodeType::INLINE_CODE, "");
        } else {
            // Fallback for regular text tokens
            parent->children.push_back(new ASTNode(NodeType::TEXT, tok.value));
            ind++;
        }
    }
}

unsigned MarkdownParser::handleInlineElement(const std::vector<Token> &tokens, unsigned ind, ASTNode *parent,
                                             TokenType targetType, NodeType nodeType, const std::string &errorMsg) {
    Token tok = tokens[ind];
    unsigned closingInd = ind + 1;
    bool found = false;

    while (closingInd < tokens.size()) {
        if (tokens[closingInd].type == targetType) {
            found = true;
            break;
        }
        closingInd++;
    }

    if (!found) {
        if (!errorMsg.empty()) {
            GlobalLogger::log(tok.line, tok.col, errorMsg);
        }
        parent->children.push_back(new ASTNode(NodeType::TEXT, tok.value));
        return ind + 1;
    }

    if (nodeType == NodeType::INLINE_CODE) {
        std::string codeContent;
        for (size_t k = ind + 1; k < closingInd; ++k) {
            codeContent += tokens[k].value;
        }
        parent->children.push_back(new ASTNode(NodeType::INLINE_CODE, codeContent));
    } else {
        ASTNode *newNode = new ASTNode(nodeType);
        std::vector<Token> nested(tokens.begin() + ind + 1, tokens.begin() + closingInd);
        parseInlineContent(nested, newNode);
        parent->children.push_back(newNode);
    }
    return closingInd + 1;
}

MarkdownParser::MarkdownParser(const std::vector<Token> &tokens)
    : memTokens(tokens) {
}

ASTNode *MarkdownParser::parse() {
    ASTNode *root = new ASTNode(NodeType::ROOT);
    ASTNode *currUL = nullptr;
    ASTNode *currOL = nullptr;

    while (!isEOF()) {
        // Handle Code Blocks (```) first since they span multiple lines
        if (peek().type == TokenType::TRIPLE_BACKTICK) {
            Token start_tok = advance(); // Consume opening ```
            if (peek().type == TokenType::NEWLINE) advance();

            ASTNode *codeBlock = new ASTNode(NodeType::CODE_BLOCK);
            std::string codeContent = "";
            bool foundEnd = false;

            while (!isEOF()) {
                if (peek().type == TokenType::TRIPLE_BACKTICK) {
                    advance(); // Consume closing ```
                    foundEnd = true;
                    break;
                }
                codeContent += advance().value;
            }

            if (!foundEnd) {
                GlobalLogger::log(start_tok.line, start_tok.col, "Unterminated code block reached EOF.");
            }

            codeBlock->content = codeContent;
            root->children.push_back(codeBlock);
            currUL = currOL = nullptr;
            if (peek().type == TokenType::NEWLINE) advance();
            continue;
        }

        std::vector<Token> line = consumeLine();
        if (line.empty()) continue; // Skip empty structural rows

        // Check for Horizontal Rule
        if (line.size() == 1 && line[0].type == TokenType::TRIPLE_DASH) {
            root->children.push_back(new ASTNode(NodeType::HORIZONTAL_RULE));
            currUL = currOL = nullptr;
            continue;
        }

        // Check for Headers (Up to 6 sequential # structures)
        size_t hashCount = 0;
        while (hashCount < line.size() && line[hashCount].type == TokenType::HASH) {
            hashCount++;
        }
        if (hashCount > 0 && hashCount <= 6 && hashCount < line.size() && line[hashCount].type ==
            TokenType::SPACE) {
            ASTNode *header = new ASTNode(NodeType::HEADER, "", static_cast<int>(hashCount));
            std::vector<Token> contentTokens(line.begin() + hashCount + 1, line.end());
            parseInlineContent(contentTokens, header);
            root->children.push_back(header);
            currUL = nullptr;
            currOL = nullptr;
            continue;
        }

        // Check for Unordered Lists (- or * followed by SPACE)
        if (line.size() >= 2 && (line[0].type == TokenType::DASH || line[0].type == TokenType::STAR) && line[1].type
            == TokenType::SPACE) {
            if (!currUL) {
                currUL = new ASTNode(NodeType::UNORDERED_LIST);
                root->children.push_back(currUL);
            }
            ASTNode *item = new ASTNode(NodeType::LIST_ITEM);
            std::vector<Token> content_tokens(line.begin() + 2, line.end());
            parseInlineContent(content_tokens, item);
            currUL->children.push_back(item);
            currOL = nullptr;
            continue;
        }

        // Check for Ordered Lists (NUMBER + DOT + SPACE)
        if (line.size() >= 3 && line[0].type == TokenType::NUMBER && line[1].type == TokenType::DOT && line[2].type
            == TokenType::SPACE) {
            if (!currOL) {
                currOL = new ASTNode(NodeType::ORDERED_LIST);
                root->children.push_back(currOL);
            }
            ASTNode *item = new ASTNode(NodeType::LIST_ITEM, line[0].value); // track number tag
            std::vector<Token> content_tokens(line.begin() + 3, line.end());
            parseInlineContent(content_tokens, item);
            currOL->children.push_back(item);
            currUL = nullptr;
            continue;
        }

        // Otherwise, fall back to standard Text Paragraph
        ASTNode *paragraph = new ASTNode(NodeType::PARAGRAPH);
        parseInlineContent(line, paragraph);
        root->children.push_back(paragraph);
        currUL = currOL = nullptr;
    }

    return root;
}

