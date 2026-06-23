//
// Created by Sybatron on 6/15/2026.
//

#include "GlobalLogger.h"

std::vector<std::string> GlobalLogger::mErrors{};

void GlobalLogger::log(unsigned line, unsigned col, const std::string &msg) {
    mErrors.push_back("Error [Line " + std::to_string(line) + ", Col " + std::to_string(col) + "]: " + msg);
}

bool GlobalLogger::hasErrors() {
    return !mErrors.empty();
}

void GlobalLogger::print() {
    for (const std::string &err: mErrors) std::cerr << err << std::endl;
}

void GlobalLogger::clear() {
    mErrors.clear();
}
