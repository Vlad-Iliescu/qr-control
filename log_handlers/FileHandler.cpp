#include "FileHandler.h"

#include <cstdlib>

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
        const char *nl = this->isAppendNewLine() ? "\n" : "";

        fprintf(this->file, "%s main.%s: %s%s", time, LogHandler::levelStr(level), msg, nl);
        fflush(this->file);

        free(time);
    }
}
