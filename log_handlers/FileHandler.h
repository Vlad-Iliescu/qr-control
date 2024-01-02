#ifndef QR_CONTROL_FILEHANDLER_H
#define QR_CONTROL_FILEHANDLER_H

#include "LogHandler.h"
#include <fstream>

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
