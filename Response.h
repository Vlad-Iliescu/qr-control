#ifndef FACE_CONTROL_RESPONSE_H
#define FACE_CONTROL_RESPONSE_H

#include <cstdlib>
#include <cstring>

typedef unsigned char byte;

class Response {

public:
    byte *data = nullptr;
    size_t size;

    Response();

    Response (const Response& other);

    Response& operator= (const Response& other);

    virtual ~Response();

    size_t append(size_t size, void *data);

    int http_code;
};


#endif //FACE_CONTROL_RESPONSE_H
