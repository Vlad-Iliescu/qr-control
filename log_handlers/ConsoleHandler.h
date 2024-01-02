#ifndef QR_CONTROL_CONSOLEHANDLER_H
#define QR_CONTROL_CONSOLEHANDLER_H


#include "LogHandler.h"

class ConsoleHandler : public LogHandler {
private:
    void log(LogLevel level, const char *msg) override;
};


#endif //QR_CONTROL_CONSOLEHANDLER_H
