#ifndef FACE_CONTROL_REQUEST_H
#define FACE_CONTROL_REQUEST_H

#include <curl/curl.h>
#include <cstdlib>
#include <cstring>
#include "Response.h"
#include "Logger.h"

class Request {
private:
    CURL *curl;
    const char *username = nullptr;
    const char *password = nullptr;
    const char *host = nullptr;
    bool debug = false;
    bool initOk;
    Logger *logger;

public:
    Request();

    explicit Request(Logger *logger);

    virtual ~Request();

    const char *getUsername() const;

    void setUsername(const char *username);

    const char *getPassword() const;

    void setPassword(const char *password);

    const char *getHost() const;

    void setHost(const char *host);

    bool isDebug() const;

    void setDebug(bool debug);

    bool isInitOk() const;

    Response get(const char *url);

    int get(const char *url, FILE *file);

    Response post(const char *url, byte *data, size_t size);

    Logger *getLogger() const;

    void setLogger(Logger *logger);

private:
    static size_t write_data(void *contents, size_t size, size_t nmemb, FILE *stream);

    static size_t write_memory(void *contents, size_t size, size_t nmemb, void *stream);

    static int curlLog(CURL *handle, curl_infotype type, char *data, size_t size, void *userp);

    void addBasicAuth();

    void addURL(const char *url);

    void setVerbosity();

    int doCall();
};


#endif //FACE_CONTROL_REQUEST_H
