//#include <iostream>
#include "Response.h"

using namespace std;

Response::Response() {
//    std::cout << "new" << std::endl;
    this->size = 0;
    this->http_code = 0;
}

Response::~Response() {
    if (this->data != nullptr) {
//        std::cout << "~" << std::endl;
        free(this->data);
        this->data = nullptr;
    }
}

size_t Response::append(size_t size, void *data) {
    if (this->data == nullptr) {
        this->data = (byte *) malloc(sizeof(byte));
    }

    this->data = static_cast<byte *>(std::realloc(this->data, this->size + size + 1));

    if (this->data == nullptr) {
        /* out of memory! */
        return 0;
    }

    std::memcpy(&(this->data[this->size]), data, size);
    this->size += size;
    this->data[this->size] = 0;

    return size;
}

Response::Response(const Response &other) {
//    std::cout << "copy";
    if (&other == this) {
        return;
    }
    if (this->data != nullptr) {
//        std::cout << " + free";
        free(this->data);
    }

    this->data = static_cast<byte *>(malloc(other.size));
    memcpy(this->data, other.data, other.size);
    this->size = other.size;
    this->http_code = other.http_code;
//    std::cout << std::endl;
}

Response &Response::operator=(const Response &other) {
//    std::cout << "=";
    if (&other == this) {
        return *this;
    }

    if (this->data != nullptr) {
//        std::cout << " + free";
        free(this->data);
    }
//    free(this->data);
    this->data = static_cast<byte *>(malloc(other.size));
    memcpy(this->data, other.data, other.size);
    this->size = other.size;
    this->http_code = other.http_code;
//    std::cout << std::endl;

    return *this;
}
