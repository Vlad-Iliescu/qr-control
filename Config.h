#ifndef FACE_CONTROL_CONFIG_H
#define FACE_CONTROL_CONFIG_H

#include "rapidjson/document.h"

typedef struct {
    char *host;
    char *image_path;
    char *user;
    char *password;
} camera_t;

typedef struct {
    char *host;
    char *path;
    char *user;
    char *password;
} pms_t;

class Config {
public:
    camera_t *camera = new camera_t;
    pms_t *pms = new pms_t;
    int log_level = 0;
    char *log_file = nullptr;
    bool log_console = false;

    Config(const char *json_file);

    virtual ~Config();

private:
    void readString(char **to, size_t size, const char *data);

    void validateDocument(const rapidjson::Document &document);
};


#endif //FACE_CONTROL_CONFIG_H
