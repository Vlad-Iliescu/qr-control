#include "ConsoleHandler.h"

#include <cstdio>
#include <cstdlib>

void ConsoleHandler::log(LogLevel level, const char *msg) {
    char *const time = LogHandler::formattedTime();
    const char *nl = this->isAppendNewLine() ? "\n" : "";

    this->beginLine(level);
    fprintf(stderr, "%s main.%s: %s%s", time, LogHandler::levelStr(level), msg, nl);
    this->endLine(level);

    free(time);
}

void ConsoleHandler::beginLine(LogLevel level) {
    fprintf(stderr, LogHandler::getColor(level));
}

void ConsoleHandler::endLine(LogLevel level) {
    fprintf(stderr, "\e[0m");
}
