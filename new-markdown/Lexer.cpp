//
// Created by Sybatron on 6/15/2026.
//

#include "Lexer.h"

char Lexer::getChar() {
    char symb = memInput.get();
    int nextCol = mCol + 1;
    int nextLine = mLine;
    if (symb == '\n') {
        nextLine++;
        nextCol = 0;
    }

    mCol = nextCol;
    mLine = nextLine;
    return symb;
}

char Lexer::peekChar() const {
    return memInput.peek();
}

Lexer::Lexer(std::istream &input)
    : memInput(input) {
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (memInput.good()) {
        char ch = peekChar();
        if (ch == EOF) break;

        // Handle Newlines
        if (ch == '\n') {
            getChar();
            tokens.push_back({TokenType::NEWLINE, "\n", mLine, mCol});
            continue;
        }

        // Handle Spaces
        if (ch == ' ') {
            getChar();
            tokens.push_back({TokenType::SPACE, " ", mLine, mCol});
            continue;
        }

        // Handle Headers (#)
        if (ch == '#') {
            getChar();
            tokens.push_back({TokenType::HASH, "#", mLine, mCol});
            continue;
        }

        // Handle Bold & Italics (*)
        if (ch == '*') {
            getChar();
            if (peekChar() == '*') {
                getChar();
                tokens.push_back({TokenType::DOUBLE_STAR, "**", mLine, mCol});
            } else {
                tokens.push_back({TokenType::STAR, "*", mLine, mCol});
            }
            continue;
        }

        // Handle Dash / Horizontal Rule (-)
        if (ch == '-') {
            getChar();
            // Check if it's a Horizontal Rule (---)
            if (peekChar() == '-') {
                getChar();
                if (peekChar() == '-') {
                    getChar();
                    tokens.push_back({TokenType::TRIPLE_DASH, "---", mLine, mCol});
                    continue;
                }
                tokens.push_back({TokenType::DASH, "-", mLine, mCol});
                tokens.push_back({TokenType::DASH, "-", mLine, mCol});
                continue;
            }
            tokens.push_back({TokenType::DASH, "-", mLine, mCol});
            continue;
        }

        // Handle Strikethrough (~~)
        if (ch == '~') {
            getChar();
            if (peekChar() == '~') {
                getChar();
                tokens.push_back({TokenType::DOUBLE_TILDE, "~~", mLine, mCol});
            } else {
                tokens.push_back({TokenType::TILDE, "~", mLine, mCol});
            }
            continue;
        }

        // Handle Code Blocks & Inline Code (`)
        if (ch == '`') {
            getChar();
            if (peekChar() == '`') {
                getChar();
                if (peekChar() == '`') {
                    getChar();
                    tokens.push_back({TokenType::TRIPLE_BACKTICK, "```", mLine, mCol});
                    continue;
                }
                tokens.push_back({TokenType::BACKTICK, "`", mLine, mCol});
                tokens.push_back({TokenType::BACKTICK, "`", mLine, mCol});
                continue;
            }
            tokens.push_back({TokenType::BACKTICK, "`", mLine, mCol});
            continue;
        }

        // Handle Numbers
        if (isdigit(ch)) {
            std::string numStr;
            while (isdigit(peekChar())) {
                numStr += getChar();
            }
            tokens.push_back({TokenType::NUMBER, numStr, mLine, mCol});
            continue;
        }

        // Handle Dots
        if (ch == '.') {
            getChar();
            tokens.push_back({TokenType::DOT, ".", mLine, mCol});
            continue;
        }

        // Default: Match plain alphanumeric text strings
        std::string textStr;
        while (memInput.good() && peekChar() != EOF &&
               peekChar() != '\n' && peekChar() != '#' &&
               peekChar() != '*' && peekChar() != '-' &&
               peekChar() != '~' && peekChar() != '`' &&
               peekChar() != ' ' && !isdigit(peekChar()) && peekChar() != '.') {
            textStr += getChar();
        }
        if (!textStr.empty()) {
            tokens.push_back({TokenType::TEXT, textStr, mLine, mCol});
        }
    }
    tokens.push_back({TokenType::END_OF_FILE, "", mLine, mCol});
    return tokens;
}
