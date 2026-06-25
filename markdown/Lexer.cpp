//
// Created by Sybatron on 6/15/2026.
//

#include "Lexer.h"
#include "Utility.h"


char Lexer::getChar() {
    char symb = memInput.get();
    unsigned nextCol = mCol + 1;
    unsigned nextLine = mLine;
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

        switch (ch) {
            case '\r':
            case '\n': handleNewline(tokens);
                break;
            case ' ': handleSpace(tokens);
                break;
            case '#': handleHash(tokens);
                break;
            case '*': handleStar(tokens);
                break;
            case '-': handleDash(tokens);
                break;
            case '~': handleTilde(tokens);
                break;
            case '`': handleBacktick(tokens);
                break;
            case '.': handleDot(tokens);
                break;

            default:
                if (Utility::isDigit(ch)) {
                    handleNumber(tokens);
                } else {
                    handleText(tokens);
                }
                break;
        }
    }

    tokens.push_back({TokenType::END_OF_FILE, "", mLine, mCol});
    return tokens;
}

void Lexer::handleBackslash(std::vector<Token> &tokens) {
    getChar(); // Consume the '\\' itself

    char next = peekChar();

    if (Utility::isEscapable(next)) {
        char escapedChar = getChar();
        std::string literalStr(1, escapedChar);

        tokens.push_back({TokenType::TEXT, literalStr, mLine, mCol});
    } else {
        tokens.push_back({TokenType::TEXT, "\\", mLine, mCol});
    }
}

void Lexer::handleNewline(std::vector<Token> &tokens) {
    if (peekChar() == '\r') {
        getChar();
        if (peekChar() == '\n') {
            getChar();
        }
    }
    if (peekChar() == '\n') {
        getChar();
    }
    tokens.push_back({TokenType::NEWLINE, "\n", mLine, mCol});
}

void Lexer::handleSpace(std::vector<Token> &tokens) {
    getChar();
    tokens.push_back({TokenType::SPACE, " ", mLine, mCol});
}

void Lexer::handleHash(std::vector<Token> &tokens) {
    getChar();
    tokens.push_back({TokenType::HASH, "#", mLine, mCol});
}

//TODO FIX TRIPLE STAR PROBLEM
void Lexer::handleStar(std::vector<Token> &tokens) {
    getChar();
    if (peekChar() == '*') {
        // if (starCount >= 3) {
        //     tokens.push_back({TokenType::STAR, "*", mLine, mCol});
        //     starCount--;
        //     return;
        // }
        // if (peekChar() == '*') {
        //     isTripleStar = true;
        // }

        getChar();
        // starCount++;
        tokens.push_back({TokenType::DOUBLE_STAR, "**", mLine, mCol});
    } else {
        tokens.push_back({TokenType::STAR, "*", mLine, mCol});
        mStarCount--;
    }
}

void Lexer::handleDash(std::vector<Token> &tokens) {
    getChar();
    if (peekChar() == '-') {
        getChar();
        if (peekChar() == '-') {
            getChar();
            tokens.push_back({TokenType::TRIPLE_DASH, "---", mLine, mCol});
            return;
        }
        tokens.push_back({TokenType::DASH, "-", mLine, mCol});
        tokens.push_back({TokenType::DASH, "-", mLine, mCol});
        return;
    }
    tokens.push_back({TokenType::DASH, "-", mLine, mCol});
}

void Lexer::handleTilde(std::vector<Token> &tokens) {
    getChar();
    if (peekChar() == '~') {
        getChar();
        tokens.push_back({TokenType::DOUBLE_TILDE, "~~", mLine, mCol});
    } else {
        tokens.push_back({TokenType::TILDE, "~", mLine, mCol});
    }
}

void Lexer::handleBacktick(std::vector<Token> &tokens) {
    getChar();
    if (peekChar() == '`') {
        getChar();
        if (peekChar() == '`') {
            getChar();
            tokens.push_back({TokenType::TRIPLE_BACKTICK, "```", mLine, mCol});
            return;
        }
        tokens.push_back({TokenType::BACKTICK, "`", mLine, mCol});
        tokens.push_back({TokenType::BACKTICK, "`", mLine, mCol});
        return;
    }
    tokens.push_back({TokenType::BACKTICK, "`", mLine, mCol});
}

void Lexer::handleDot(std::vector<Token> &tokens) {
    getChar();
    tokens.push_back({TokenType::DOT, ".", mLine, mCol});
}

void Lexer::handleNumber(std::vector<Token> &tokens) {
    std::string numStr;
    while (Utility::isDigit(peekChar())) {
        numStr += getChar();
    }
    tokens.push_back({TokenType::NUMBER, numStr, mLine, mCol});
}

void Lexer::handleText(std::vector<Token> &tokens) {
    std::string textStr;

    while (memInput.good() && peekChar() != EOF &&
           peekChar() != '\n' && peekChar() != '#' &&
           peekChar() != '*' && peekChar() != '-' &&
           peekChar() != '~' && peekChar() != '`' &&
           peekChar() != ' ' && !Utility::isDigit(peekChar()) && peekChar() != '.') {
        textStr += getChar();
    }
    if (!textStr.empty()) {
        tokens.push_back({TokenType::TEXT, textStr, mLine, mCol});
    }
}
