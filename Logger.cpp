#include "Logger.h"

#include <ctime>
#include <iostream>

using namespace std;

#ifdef _WIN32
#define _mkdir(pathname, mode) mkdir(pathname)
#else
#define _mkdir(pathname, mode) mkdir(pathname, mode)
#endif

Logger::Logger(log_strategy strategy, const char *path, t_debug minimum_level) : strategy(strategy),
                                                                                 min_level(minimum_level), path(path) {
    if (this->strategy == LOG_TO_FILE) {
        std::cout << "LOG_TO_FILE: " << this->path << std::endl;

//        struct stat st = {0};
//        if (stat(this->path, &st) == -1) {
//            std::cout << "mkdir: " << this->path << std::endl;
//            _mkdir(this->path, 0755);
//        }

        this->log_file.open(this->path, ios::out | ios::app);
    }
}

Logger::~Logger() {
    if (this->strategy == LOG_TO_FILE) {
        this->log_file.close();
    }
}

Logger::Logger(log_strategy strategy, t_debug minimum_level) : strategy(strategy), min_level(minimum_level) {}

std::ofstream &Logger::info() {
    char tmp_str[100];
    time_t cur_time = time(nullptr);
    strftime(tmp_str, 100, "[%Y-%m-%d %H:%M:%S]", localtime(&cur_time));


    this->log_file << "\n"
                   << tmp_str
                   << "[INFO]";

    std::cout << std::endl
              << tmp_str
              << "[INFO]";

    this->log_file.flush();
    return this->log_file;
}

