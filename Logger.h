#ifndef QR_CONTROL_LOGGER_H
#define QR_CONTROL_LOGGER_H

#include <cstdio>
#include <fstream>

typedef enum {
    LEVEL_EMERGENCY = 0, // will always be logged
    LEVEL_ALERT = 1, // will be logged on debug lvl 1 and above
    LEVEL_CRITICAL = 2, // same as above only on lvl 2
    LEVEL_ERROR = 3,
    LEVEL_WARNING = 4,
    LEVEL_NOTICE = 5,
    LEVEL_INFO = 6,
    LEVEL_DEBUG = 7
} t_debug;

typedef enum {
    LOG_TO_FILE,
    LOG_TO_CONSOLE,
    NO_LOGGING
} log_strategy;


class Logger {
private:
    const char *path = nullptr;
    t_debug min_level;
    log_strategy strategy;
    std::ofstream log_file;
public:
    Logger(log_strategy strategy, t_debug minimum_level);

    Logger(log_strategy strategy, const char *path, t_debug minimum_level);

    virtual ~Logger();

    std::ofstream &info();
};


#endif //QR_CONTROL_LOGGER_H
