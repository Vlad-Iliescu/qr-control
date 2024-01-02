#ifndef QR_CONTROL_LOGGER_H
#define QR_CONTROL_LOGGER_H

#include <cstdio>
#include <fstream>
#include <vector>
#include "log_handlers/LogHandler.h"
#include "log_handlers/FileHandler.h"

typedef enum {
    LOG_TO_FILE,
    LOG_TO_CONSOLE,
    NO_LOGGING
} log_strategy;


class Logger {
private:
    LogLevel min_level;
    std::vector<LogHandler *> handlers;

public:
    Logger(LogLevel minimum_level);

    virtual ~Logger();

    void addHandlers(LogHandler *handler);

    void debug(const char *msg);

    void info(const char *msg);

    void notice(const char *msg);

    void warning(const char *msg);

    void error(const char *msg);

    void critical(const char *msg);

    void alert(const char *msg);

    void emergency(const char *msg);
};


#endif //QR_CONTROL_LOGGER_H
