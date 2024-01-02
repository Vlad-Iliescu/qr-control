//#include <iostream>
#include "Request.h"

using namespace std;

size_t Request::write_data(void *contents, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(contents, size, nmemb, stream);
    return written;
}

size_t Request::write_memory(void *contents, size_t size, size_t nmemb, void *stream) {
    size_t realsize = size * nmemb;
    auto *mem = (Response *) stream;

    return mem->append(realsize, contents);
}

Request::Request() {
    this->curl = curl_easy_init();

    this->initOk = (bool) this->curl;
}

Response Request::get(const char *url) {
    this->setVerbosity();
    this->addBasicAuth();
    this->addURL(url);

    Response chunk;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Request::write_memory);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &chunk.http_code);

    }

    return chunk;
}

Request::~Request() {
    curl_easy_cleanup(this->curl);
}

CURLcode Request::get(const char *url, FILE *file) {
    this->setVerbosity();
    this->addBasicAuth();
    this->addURL(url);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Request::write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

    return curl_easy_perform(curl);
}

const char *Request::getUsername() const {
    return username;
}

void Request::setUsername(const char *username) {
    this->username = username;
}

const char *Request::getPassword() const {
    return password;
}

void Request::setPassword(const char *password) {
    this->password = password;
}

const char *Request::getHost() const {
    return host;
}

void Request::setHost(const char *host) {
    this->host = host;
}

bool Request::isInitOk() const {
    return this->initOk;
}

void Request::addBasicAuth() {
    if (this->getUsername() && this->getPassword()) {
        curl_easy_setopt(this->curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(this->curl, CURLOPT_USERNAME, this->getUsername());
        curl_easy_setopt(this->curl, CURLOPT_PASSWORD, this->getPassword());
    }
}

void Request::addURL(const char *url) {
    if (this->getHost() && url) {
        const size_t size = strlen(this->getHost()) + strlen(url) + 1; // account for '\0'
        auto *buffer = static_cast<char *>(std::calloc(size, sizeof(char)));
        sprintf(buffer, "%s%s", this->getHost(), url);
        curl_easy_setopt(this->curl, CURLOPT_URL, buffer);
    }
}

Response Request::post(const char *url, byte *data, size_t size) {
//    std::cout << "DO POST" << std::endl;
    this->setVerbosity();
    this->addBasicAuth();
    this->addURL(url);

    struct curl_httppost *formpost = nullptr;
    struct curl_httppost *lastptr = nullptr;

    curl_formadd(&formpost, &lastptr,
                 CURLFORM_COPYNAME, "picture",
                 CURLFORM_BUFFER, "picture",
                 CURLFORM_BUFFERPTR, data,
                 CURLFORM_BUFFERLENGTH, size,
                 CURLFORM_CONTENTTYPE, "image/jpg",
                 CURLFORM_END);

    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    Response chunk;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Request::write_memory);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &chunk.http_code);
    }

    return chunk;
}

void Request::setVerbosity() {
    if (this->isDebug()) {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    }
}

bool Request::isDebug() const {
    return this->debug;
}

void Request::setDebug(bool debug) {
    this->debug = debug;
}
