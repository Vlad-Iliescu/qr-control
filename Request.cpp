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

Request::Request(Logger *logger) : logger(logger) {
    this->getLogger()->debug("Initializing cURL.");

    this->curl = curl_easy_init();
    this->initOk = (bool) this->curl;

    if (this->initOk) {
        this->getLogger()->debug("Initialized OK!");
    } else {
        this->getLogger()->error("Failed to initialize!");
    }
}

Response Request::get(const char *url) {
    this->getLogger()->debug("Starting GET request.");
    this->setVerbosity();
    this->addBasicAuth();
    this->addURL(url);

    Response chunk;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Request::write_memory);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

    this->getLogger()->debug("Calling cURL.");
    chunk.http_code = this->doCall();

    return chunk;
}

Request::~Request() {
    curl_easy_cleanup(this->curl);
}

int Request::get(const char *url, FILE *file) {
    this->getLogger()->debug("Starting GET request.");
    this->setVerbosity();
    this->addBasicAuth();
    this->addURL(url);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Request::write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

    this->getLogger()->debug("Calling cURL. Result will be saved to file.");
    return this->doCall();
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
        this->getLogger()->debug(
                "Adding Basic Authentication [%s:%c***].",
                this->getUsername(),
                this->getPassword()[0]
        );
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

        this->getLogger()->debug("Setting url [%s].", buffer);
        curl_easy_setopt(this->curl, CURLOPT_URL, buffer);
    }
}

Response Request::post(const char *url, byte *data, size_t size) {
    this->getLogger()->debug("Starting POST request.");
    this->setVerbosity();
    this->addBasicAuth();
    this->addURL(url);

    struct curl_httppost *formpost = nullptr;
    struct curl_httppost *lastptr = nullptr;

    this->getLogger()->debug("Adding form data [name='picture'][content-type='image/jpeg'][size=%d].", size);
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

    chunk.http_code = this->doCall();

    return chunk;
}

void Request::setVerbosity() {
    if (this->isDebug()) {
        this->getLogger()->debug("Debug is on");
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, Request::curlLog);
        curl_easy_setopt(curl, CURLOPT_DEBUGDATA, this->logger);
    }
}

bool Request::isDebug() const {
    return this->debug;
}

void Request::setDebug(bool debug) {
    this->debug = debug;
}

Logger *Request::getLogger() const {
    return logger;
}

void Request::setLogger(Logger *logger) {
    this->logger = logger;
}

int Request::doCall() {
    CURLcode res = curl_easy_perform(this->curl);
    int httpCode = 0;

    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        this->getLogger()->info("%d", httpCode);
        if (200 > httpCode || httpCode >= 400) {
            this->getLogger()->warning("cURL returned HTTP code %d.", httpCode);
        }
    } else {
        this->getLogger()->error("cURL error: %s.", curl_easy_strerror(res));
    }

    return httpCode;
}

int Request::curlLog(CURL *handle, curl_infotype type, char *data, size_t size, void *userp) {
    const char *text = nullptr;
    (void) handle; /* prevent compiler warning */
    (void) userp;
    auto *logger = static_cast<Logger *>(userp);


    switch (type) {
        case CURLINFO_TEXT:
            text = "[cURL]";
            break;
        case CURLINFO_HEADER_OUT:
            text = "[cURL][Send header]";
            break;
        case CURLINFO_HEADER_IN:
            text = "[cURL][Recv header]";
            break;

        case CURLINFO_DATA_OUT:
        case CURLINFO_SSL_DATA_OUT:
            logger->debug("[cURL][Sending][%db]", size);
            return 0;
        case CURLINFO_DATA_IN:
        case CURLINFO_SSL_DATA_IN:
            logger->debug("[cURL][Receiving][%db]", size);
            return 0;
        default:
            return 0; // do not print data
    }
    logger->setAutoAppendNewLine(false);
    logger->debug("%s[%db]%s", text, size, data);
    logger->setAutoAppendNewLine(true);

    return 0;
}
