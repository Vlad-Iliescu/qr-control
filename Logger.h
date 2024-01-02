#ifndef QR_CONTROL_LOGGER_H
#define QR_CONTROL_LOGGER_H

#include <vector>
#include <cstdarg>
#include "log_handlers/LogHandler.h"

class Logger {
private:
    LogLevel min_level;
    std::vector<LogHandler *> handlers;

public:
    explicit Logger(LogLevel minimum_level);

    virtual ~Logger();

    void addHandlers(LogHandler *handler);

    void debug(const char* format, ...);

    void info(const char* format, ...);

    void notice(const char* format, ...);

    void warning(const char* format, ...);

    void error(const char* format, ...);

    void critical(const char* format, ...);

    void alert(const char* format, ...);

    void emergency(const char *format, ...);

    void setAutoAppendNewLine(bool appendNL);
};


#endif //QR_CONTROL_LOGGER_H
