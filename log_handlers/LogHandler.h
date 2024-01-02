#ifndef QR_CONTROL_LOGHANDLER_H
#define QR_CONTROL_LOGHANDLER_H

typedef enum {
    LEVEL_EMERGENCY = 0, // will always be logged
    LEVEL_ALERT = 1, // will be logged on debug lvl 1 and above
    LEVEL_CRITICAL = 2, // same as above only on lvl 2
    LEVEL_ERROR = 3,
    LEVEL_WARNING = 4,
    LEVEL_NOTICE = 5,
    LEVEL_INFO = 6,
    LEVEL_DEBUG = 7
} LogLevel;

class LogHandler {
private:
    bool appendNewLine = true;

    virtual void log(LogLevel level, const char *msg) = 0;

    virtual void beginLine(LogLevel level) {};

    virtual void endLine(LogLevel level) {};

public:
    void debug(const char *msg);

    void info(const char *msg);

    void notice(const char *msg);

    void warning(const char *msg);

    void error(const char *msg);

    void critical(const char *msg);

    void alert(const char *msg);

    void emergency(const char *msg);

    bool isAppendNewLine() const;

    void setAppendNewLine(bool appendNewLine);

    static const char *levelStr(LogLevel debug_level);

    static const char *getColor(LogLevel level);

    static char *formattedTime();
};


#endif //QR_CONTROL_LOGHANDLER_H
