#include "ConsoleHandler.h"

#include <cstdio>
#include <cstdlib>

void ConsoleHandler::log(LogLevel level, const char *msg) {
    char *const time = LogHandler::formattedTime();

    this->beginLine(level);
    fprintf(stderr, "%s main.%s: %s\n", time, LogHandler::levelStr(level), msg);
    this->endLine(level);

    free(time);
}

void ConsoleHandler::beginLine(LogLevel level) {
    fprintf(stderr, LogHandler::getColor(level));
}

void ConsoleHandler::endLine(LogLevel level) {
    fprintf(stderr, "\e[0m");
}
