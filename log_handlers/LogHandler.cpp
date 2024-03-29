#include "LogHandler.h"

#include <ctime>
#include <cstdlib>

void LogHandler::debug(const char *msg) {
    this->log(LogLevel::LEVEL_DEBUG, msg);
}

void LogHandler::info(const char *msg) {
    this->log(LogLevel::LEVEL_INFO, msg);
}

void LogHandler::notice(const char *msg) {
    this->log(LogLevel::LEVEL_NOTICE, msg);
}

void LogHandler::warning(const char *msg) {
    this->log(LogLevel::LEVEL_WARNING, msg);
}

void LogHandler::error(const char *msg) {
    this->log(LogLevel::LEVEL_ERROR, msg);
}

void LogHandler::critical(const char *msg) {
    this->log(LogLevel::LEVEL_CRITICAL, msg);
}

void LogHandler::alert(const char *msg) {
    this->log(LogLevel::LEVEL_ALERT, msg);
}

void LogHandler::emergency(const char *msg) {
    this->log(LogLevel::LEVEL_EMERGENCY, msg);
}

const char *LogHandler::levelStr(LogLevel debug_level) {
    switch (debug_level) {
        case LogLevel::LEVEL_EMERGENCY:
            return "EMERGENCY";
        case LogLevel::LEVEL_ALERT:
            return "ALERT";
        case LogLevel::LEVEL_CRITICAL:
            return "CRITICAL";
        case LogLevel::LEVEL_ERROR:
            return "ERROR";
        case LogLevel::LEVEL_WARNING:
            return "WARNING";
        case LogLevel::LEVEL_NOTICE:
            return "NOTICE";
        case LogLevel::LEVEL_INFO:
            return "INFO";
        case LogLevel::LEVEL_DEBUG:
            return "DEBUG";
        default:
            return "UNKNOWN";
    }
}

char *LogHandler::formattedTime() {
    auto *tmp_str = static_cast<char *>(calloc(50, sizeof(char)));
    time_t cur_time = time(nullptr);
    strftime(tmp_str, 50, "[%Y-%m-%d %H:%M:%S]", localtime(&cur_time));
    return tmp_str;
}

const char *LogHandler::getColor(LogLevel level) {
    switch (level) {
        case LogLevel::LEVEL_EMERGENCY:
            return "\e[1m\e[38;5;1m";
        case LogLevel::LEVEL_ALERT:
            return "\e[31m";
        case LogLevel::LEVEL_CRITICAL:
            return "\e[91m";
        case LogLevel::LEVEL_ERROR:
            return "\e[38;5;202m";
        case LogLevel::LEVEL_WARNING:
            return "\e[33m";
        case LogLevel::LEVEL_NOTICE:
            return "\e[35m";
        case LogLevel::LEVEL_INFO:
            return "\e[34m";
        case LogLevel::LEVEL_DEBUG:
            return "\e[38;5;28m";
        default:
            return "";
    }
}

bool LogHandler::isAppendNewLine() const {
    return appendNewLine;
}

void LogHandler::setAppendNewLine(bool appendNewLine) {
    this->appendNewLine = appendNewLine;
}
