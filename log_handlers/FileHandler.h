#ifndef QR_CONTROL_FILEHANDLER_H
#define QR_CONTROL_FILEHANDLER_H

#include <cstdio>
#include "LogHandler.h"

class FileHandler : public LogHandler {
private:
    const char *path;
    FILE *file;

public:
    explicit FileHandler(const char *path);

    virtual ~FileHandler();

private:
    void log(LogLevel level, const char *msg) override;
};


#endif //QR_CONTROL_FILEHANDLER_H
