//
// Created by Sybatron on 5/16/2026.
//

#include "Cli.h"

Cli::Cli() {
    // parser = new MarkdownParser();
    // lexer = new Lexer();
}

Cli::~Cli() {
    delete lexer;
    delete parser;
}

void Cli::run() {
    std::string cliInput;
    std::getline(std::cin, cliInput);

    if (cliInput == "exit") {
        return;
    }
}

void Cli::translate(std::string input, std::string output) {
}

void Cli::print(std::string input) {
}

void Cli::validate(std::string input) {
}
