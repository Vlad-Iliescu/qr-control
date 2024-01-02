#ifndef FACE_CONTROL_REQUEST_H
#define FACE_CONTROL_REQUEST_H

#include <curl/curl.h>
#include <cstdlib>
#include <cstring>
#include "Response.h"

class Request {
private:
    CURL *curl;
    const char *username = nullptr;
    const char *password = nullptr;
    const char *host = nullptr;
    bool debug = false;
    bool initOk;

public:
    Request();

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

    CURLcode get(const char *url, FILE *file);

    Response post(const char *url, byte *data, size_t size);

private:
    static size_t write_data(void *contents, size_t size, size_t nmemb, FILE *stream);

    static size_t write_memory(void *contents, size_t size, size_t nmemb, void *stream);

    void addBasicAuth();

    void addURL(const char *url);

    void setVerbosity();
};


#endif //FACE_CONTROL_REQUEST_H
