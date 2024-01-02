#ifndef QR_CONTROL_CONSOLEHANDLER_H
#define QR_CONTROL_CONSOLEHANDLER_H


#include "LogHandler.h"

class ConsoleHandler : public LogHandler {
private:
    void log(LogLevel level, const char *msg) override;
    void beginLine(LogLevel level) override;
    void endLine(LogLevel level) override;
};


#endif //QR_CONTROL_CONSOLEHANDLER_H
