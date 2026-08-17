//
// Created by Sybatron on 5/16/2026.
//

#include "Cli.h"

#include <iostream>

#include "Utility.h"

Cli::Cli() {
    // parser = new MarkdownParser();
    // lexer = new Lexer();
}

Cli::~Cli() {
    delete lexer;
    delete parser;
    delete htmlWriter;
}

void Cli::run() {
    std::string cliInput;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, cliInput)) {
            break;
        }
        if (cliInput == "exit") {
            break;
        }

        std::vector<std::string> args = parseArguments(cliInput);
        GlobalLogger::clear();
        try {
            executeCommand(args);
        } catch (...) {
            std::cout << "\n--- ERROR LOGGER LOGS ---\n";
            if (GlobalLogger::hasErrors()) {
                GlobalLogger::print();
            } else {
                delete htmlWriter;
                delete parser;
                delete lexer;
                throw;
            }
        }
    }
}

void Cli::translate(std::string input, std::string output) {
    std::cout << "[Translating] From: " << input << " To: " << output << "\n";
    std::ifstream inputFile(std::string(SUBDIR_ASSET_PATH) + input);
    if (!inputFile) {
        GlobalLogger::log(0, 0, "File does not exist.");
        return;
    }

    try {
        lexer = new Lexer(inputFile);
    } catch (std::exception &e) {
        inputFile.close();
        GlobalLogger::log(0, 0, "AST lexer couldn't be parsed: " + std::string(e.what()));
        return;
    } catch (...) {
        inputFile.close();
        throw;
    }
    std::vector<Token> tokens = lexer->tokenize();
    inputFile.close();


    try {
        parser = new MarkdownParser(tokens);
    } catch (...) {
        GlobalLogger::log(0, 0, "Error memory alloc parser");
        throw;
    }
    bool didBreak = false;

    ASTNode *treeRoot = nullptr;
    try {
        treeRoot = parser->parse();
    } catch (std::exception &e) {
        didBreak = true;
        delete treeRoot;
        GlobalLogger::log(0, 0, "AST tree couldn't be parsed");
        return;
    } catch (...) {
        didBreak = true;
        delete treeRoot;
        throw;
    }

    try {
        htmlWriter = new HtmlWriter();
    } catch (...) {
        delete treeRoot;
        throw;
    }

    htmlWriter->save(treeRoot, output);
    getErrorLog();

    if (!didBreak && treeRoot != nullptr) {
        delete treeRoot;
    }
    GlobalLogger::clear();
}

void Cli::print(std::string input) {
    std::cout << "[Printing] File: " << input << "\n";
    std::ifstream inputFile(std::string(SUBDIR_ASSET_PATH) + input);
    if (!inputFile) {
        GlobalLogger::log(0, 0, "File does not exist.");
        return;
    }

    try {
        lexer = new Lexer(inputFile);
    } catch (std::exception &e) {
        inputFile.close();
        GlobalLogger::log(0, 0, "AST lexer couldn't be parsed: " + std::string(e.what()));
        return;
    } catch (...) {
        inputFile.close();
        throw;
    }
    std::vector<Token> tokens = lexer->tokenize();

    inputFile.close();


    try {
        parser = new MarkdownParser(tokens);
    } catch (...) {
        GlobalLogger::log(0, 0, "Error memory alloc parser");
        throw;
    }
    bool didBreak = false;

    ASTNode *treeRoot = nullptr;
    try {
        treeRoot = parser->parse();
        Utility::debugPrintTree(treeRoot);
    } catch (std::exception &e) {
        didBreak = true;
        delete treeRoot;
        GlobalLogger::log(0, 0, "AST tree couldn't be parsed");
        return;
    } catch (...) {
        didBreak = true;
        delete treeRoot;
        GlobalLogger::log(0, 0, "Error during AST parse");
        throw;
    }

    delete treeRoot;
}

void Cli::validate(const std::string &input) {
    std::cout << "[Validating] File: " << input << "\n";

    std::ifstream inputFile(std::string(SUBDIR_ASSET_PATH) + input);
    if (!inputFile) {
        GlobalLogger::log(0, 0, "File does not exist.");
        return;
    }

    try {
        lexer = new Lexer(inputFile);
    } catch (std::exception &e) {
        inputFile.close();
        GlobalLogger::log(0, 0, "AST lexer couldn't be parsed: " + std::string(e.what()));
        return;
    } catch (...) {
        inputFile.close();
        throw;
    }
    std::vector<Token> tokens = lexer->tokenize();

    inputFile.close();


    try {
        parser = new MarkdownParser(tokens);
    } catch (...) {
        GlobalLogger::log(0, 0, "Error memory alloc parser");
        throw;
    }
    bool didBreak = false;

    ASTNode *treeRoot = nullptr;
    try {
        treeRoot = parser->parse();
    } catch (std::exception &e) {
        didBreak = true;
        delete treeRoot;
        GlobalLogger::log(0, 0, "AST tree couldn't be parsed");
        GlobalLogger::print();
        return;
    } catch (...) {
        didBreak = true;
        delete treeRoot;
        GlobalLogger::log(0, 0, "Error during AST parse");
        GlobalLogger::print();
        throw;
    }

    getErrorLog();
    delete treeRoot;
}

bool Cli::endsWith(const std::string &str, const std::string &suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

std::vector<std::string> Cli::parseArguments(const std::string &input) {
    std::vector<std::string> args;
    std::string currentArg;
    bool inQuotes = false;

    for (size_t i = 0; i < input.length(); ++i) {
        char ch = input[i];
        if (ch == '"') {
            inQuotes = !inQuotes;
        } else if (ch == ' ' && !inQuotes) {
            if (!currentArg.empty()) {
                args.push_back(currentArg);
                currentArg.clear();
            }
        } else {
            currentArg += ch;
        }
    }
    if (!currentArg.empty()) {
        args.push_back(currentArg);
    }
    return args;
}

void Cli::executeCommand(const std::vector<std::string> &args) {
    if (args.empty()) return;

    std::string command = args[0];

    if (command == "translate") {
        if (args.size() < 3) {
            std::cerr << "Error: 'translate' requires an input and an output filepath.\n";
            return;
        }
        if (args.size() > 3) {
            std::cerr << "Error: 'translate' must have 3 arguments only \n";
            return;
        }

        std::string inputPath = args[1];
        std::string outputPath = args[2];

        // Enforce constraints: input must be .md and output must be .html
        if (!endsWith(inputPath, ".md")) {
            std::cout << "Error: Input file must be a '.md' file.\n";
            return;
        }
        if (!endsWith(outputPath, ".html")) {
            std::cout << "Error: Output file must be a '.html' file.\n";
            return;
        }

        translate(inputPath, outputPath);
    } else if (command == "print") {
        if (args.size() == 2) {
            print(args[1]);
        } else {
            std::cout << "Error: 'print' requires an input filepath and only 2 arguments \n";
        }
    } else if (command == "validate") {
        if (args.size() == 2) {
            validate(args[1]);
        } else {
            std::cout << "Error: 'validate' requires an input filepath and only 2 arguments\n";
        }
    } else {
        std::cout << "Unknown command: " << command << "\n";
    }
}

void Cli::getErrorLog() {
    std::cout << "\n--- ERROR LOGGER LOGS ---\n";
    if (GlobalLogger::hasErrors()) {
        GlobalLogger::print();
    } else {
        std::cout << "All clear! No errors registered during evaluation.\n";
    }
}




