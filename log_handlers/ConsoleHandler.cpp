#include "ConsoleHandler.h"

#include <cstdio>
#include <cstdlib>

void ConsoleHandler::log(LogLevel level, const char *msg) {
    char *const time = LogHandler::formattedTime();

    fprintf(stderr, "%s main.%s: %s\n", time, LogHandler::levelStr(level), msg);

    free(time);
}
