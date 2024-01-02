#include "FileHandler.h"

using namespace std;

FileHandler::FileHandler(const char *path) : path(path) {
    this->file = fopen(this->path, "a");
}

FileHandler::~FileHandler() {
    if (this->file != nullptr) {
        fclose(this->file);
    }
}

void FileHandler::log(LogLevel level, const char *msg) {
    if (this->file != nullptr) {
        char *const time = LogHandler::formattedTime();

        fprintf(this->file, "%s main.%s: %s\n", time, LogHandler::levelStr(level), msg);
        fflush(this->file);

        free(time);
    }
}
