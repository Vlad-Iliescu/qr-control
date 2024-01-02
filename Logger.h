#ifndef QR_CONTROL_LOGGER_H
#define QR_CONTROL_LOGGER_H

#include <vector>
#include "log_handlers/LogHandler.h"

class Logger {
private:
    LogLevel min_level;
    std::vector<LogHandler *> handlers;

public:
    explicit Logger(LogLevel minimum_level);

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
