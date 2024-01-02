#include "Logger.h"

#include <cstdio>
#include <cstdlib>

using namespace std;

//@todo: remove duplications

Logger::Logger(LogLevel minimum_level) : min_level(minimum_level) {}

Logger::~Logger() {
    for (auto &handler : this->handlers) {
        delete handler;
    }
}

void Logger::addHandlers(LogHandler *handler) {
    this->handlers.push_back(handler);
}

void Logger::debug(const char *format, ...) {
    if (this->min_level < LogLevel::LEVEL_DEBUG) {
        return;
    }
    // rebuild arguments
    va_list args;
    va_start(args, format);

    // calc and create error char*
    int needed = vsnprintf(nullptr, 0, format, args);
    auto *buff = static_cast<char *>(malloc(sizeof(char) * (needed + 1)));
    vsprintf(buff, format, args);

    // pass error to handlers
    for (auto &handler : this->handlers) {
        handler->debug(buff);
    }

    // cleanup
    free(buff);
    va_end(args);
}

void Logger::info(const char *format, ...) {
    if (this->min_level < LogLevel::LEVEL_INFO) {
        return;
    }
    // rebuild arguments
    va_list args;
    va_start(args, format);

    // calc and create error char*
    int needed = vsnprintf(nullptr, 0, format, args);
    auto *buff = static_cast<char *>(malloc(sizeof(char) * (needed + 1)));
    vsprintf(buff, format, args);

    // pass error to handlers
    for (auto &handler : this->handlers) {
        handler->info(buff);
    }

    // cleanup
    free(buff);
    va_end(args);
}

void Logger::notice(const char *format, ...) {
    if (this->min_level < LogLevel::LEVEL_NOTICE) {
        return;
    }
    // rebuild arguments
    va_list args;
    va_start(args, format);

    // calc and create error char*
    int needed = vsnprintf(nullptr, 0, format, args);
    auto *buff = static_cast<char *>(malloc(sizeof(char) * (needed + 1)));
    vsprintf(buff, format, args);

    // pass error to handlers
    for (auto &handler : this->handlers) {
        handler->notice(buff);
    }

    // cleanup
    free(buff);
    va_end(args);
}

void Logger::warning(const char *format, ...) {
    if (this->min_level < LogLevel::LEVEL_WARNING) {
        return;
    }
    // rebuild arguments
    va_list args;
    va_start(args, format);

    // calc and create error char*
    int needed = vsnprintf(nullptr, 0, format, args);
    auto *buff = static_cast<char *>(malloc(sizeof(char) * (needed + 1)));
    vsprintf(buff, format, args);

    // pass error to handlers
    for (auto &handler : this->handlers) {
        handler->warning(buff);
    }

    // cleanup
    free(buff);
    va_end(args);
}

void Logger::error(const char *format, ...) {
    if (this->min_level < LogLevel::LEVEL_ERROR) {
        return;
    }
    // rebuild arguments
    va_list args;
    va_start(args, format);

    // calc and create error char*
    int needed = vsnprintf(nullptr, 0, format, args);
    auto *buff = static_cast<char *>(malloc(sizeof(char) * (needed + 1)));
    vsprintf(buff, format, args);

    // pass error to handlers
    for (auto &handler : this->handlers) {
        handler->error(buff);
    }

    // cleanup
    free(buff);
    va_end(args);
}

void Logger::critical(const char *format, ...) {
    if (this->min_level < LogLevel::LEVEL_CRITICAL) {
        return;
    }
    // rebuild arguments
    va_list args;
    va_start(args, format);

    // calc and create error char*
    int needed = vsnprintf(nullptr, 0, format, args);
    auto *buff = static_cast<char *>(malloc(sizeof(char) * (needed + 1)));
    vsprintf(buff, format, args);

    // pass error to handlers
    for (auto &handler : this->handlers) {
        handler->critical(buff);
    }

    // cleanup
    free(buff);
    va_end(args);
}

void Logger::alert(const char *format, ...) {
    if (this->min_level < LogLevel::LEVEL_ALERT) {
        return;
    }
    // rebuild arguments
    va_list args;
    va_start(args, format);

    // calc and create error char*
    int needed = vsnprintf(nullptr, 0, format, args);
    auto *buff = static_cast<char *>(malloc(sizeof(char) * (needed + 1)));
    vsprintf(buff, format, args);

    // pass error to handlers
    for (auto &handler : this->handlers) {
        handler->alert(buff);
    }

    // cleanup
    free(buff);
    va_end(args);
}

void Logger::emergency(const char *format, ...) {
    // rebuild arguments
    va_list args;
    va_start(args, format);

    // calc and create error char*
    int needed = vsnprintf(nullptr, 0, format, args);
    auto *buff = static_cast<char *>(malloc(sizeof(char) * (needed + 1)));
    vsprintf(buff, format, args);

    // pass error to handlers
    for (auto &handler : this->handlers) {
        handler->debug(buff);
    }

    // cleanup
    free(buff);
    va_end(args);
}

void Logger::setAutoAppendNewLine(bool appendNL) {
    // pass error to handlers
    for (auto &handler : this->handlers) {
        handler->setAppendNewLine(appendNL);
    }
}
