#include "Logger.h"

using namespace std;

Logger::Logger(LogLevel minimum_level) : min_level(minimum_level) {}

Logger::~Logger() {
    for (auto &handler : this->handlers) {
        delete handler;
    }
}

void Logger::addHandlers(LogHandler *handler) {
    this->handlers.push_back(handler);
}

void Logger::debug(const char *msg) {
    if (this->min_level >= LogLevel::LEVEL_DEBUG) {
        for (auto &handler : this->handlers) {
            handler->debug(msg);
        }
    }
}

void Logger::info(const char *msg) {
    if (this->min_level >= LogLevel::LEVEL_INFO) {
        for (auto &handler : this->handlers) {
            handler->info(msg);
        }
    }
}

void Logger::notice(const char *msg) {
    if (this->min_level >= LogLevel::LEVEL_NOTICE) {
        for (auto &handler : this->handlers) {
            handler->notice(msg);
        }
    }
}

void Logger::warning(const char *msg) {
    if (this->min_level >= LogLevel::LEVEL_WARNING) {
        for (auto &handler : this->handlers) {
            handler->warning(msg);
        }
    }
}

void Logger::error(const char *msg) {
    if (this->min_level >= LogLevel::LEVEL_ERROR) {
        for (auto &handler : this->handlers) {
            handler->error(msg);
        }
    }
}

void Logger::critical(const char *msg) {
    if (this->min_level >= LogLevel::LEVEL_CRITICAL) {
        for (auto &handler : this->handlers) {
            handler->critical(msg);
        }
    }
}

void Logger::alert(const char *msg) {
    if (this->min_level >= LogLevel::LEVEL_ALERT) {
        for (auto &handler : this->handlers) {
            handler->alert(msg);
        }
    }
}

void Logger::emergency(const char *msg) {
    for (auto &handler : this->handlers) {
        handler->emergency(msg);
    }
}

