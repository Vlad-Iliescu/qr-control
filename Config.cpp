#include "Config.h"
#include "rapidjson/filereadstream.h"

using namespace rapidjson;

Config::Config(const char *json_file) {
    FILE *file = fopen(json_file, "r");
    if (file == nullptr) {
        exit(1);
    }

    // obtain file size:
    fseek(file, 0, SEEK_END);
    auto size = static_cast<size_t>(ftell(file));
    rewind(file);

    // allocate memory to contain the whole file:
    auto buffer = static_cast<char *>(calloc(size, sizeof(char)));
    FileReadStream is(file, buffer, size);

    Document document;
    document.ParseStream(is);
    if (document.HasParseError()) {
        exit(2);
    }
    fclose(file);

    // validate json integrity
    this->validateDocument(document);

    this->log_level = document["log_level"].GetInt();

    if (document.HasMember("log_file") && document["log_file"].IsString()) {
        this->readString(&this->log_file, document["log_file"].GetStringLength(), document["log_file"].GetString());
    }

    if (document.HasMember("log_console") && document["log_console"].IsBool()) {
        this->log_console = document["log_console"].GetBool();
    }

    // read camera settings
    this->readString(&this->camera->host, document["camera"]["host"].GetStringLength(),
                     document["camera"]["host"].GetString());
    this->readString(&this->camera->image_path, document["camera"]["image_path"].GetStringLength(),
                     document["camera"]["image_path"].GetString());
    this->readString(&this->camera->user, document["camera"]["user"].GetStringLength(),
                     document["camera"]["user"].GetString());
    this->readString(&this->camera->password, document["camera"]["password"].GetStringLength(),
                     document["camera"]["password"].GetString());

    // read pms settings
    this->readString(&this->pms->host, document["pms"]["host"].GetStringLength(),
                     document["pms"]["host"].GetString());
    this->readString(&this->pms->path, document["pms"]["path"].GetStringLength(),
                     document["pms"]["path"].GetString());
    this->readString(&this->pms->user, document["pms"]["user"].GetStringLength(),
                     document["pms"]["user"].GetString());
    this->readString(&this->pms->password, document["pms"]["password"].GetStringLength(),
                     document["pms"]["password"].GetString());

    // cleanup
    free(buffer);
}

void Config::readString(char **to, size_t size, const char *data) {
    *to = static_cast<char *>(calloc(size + 1, sizeof(char)));
    strcpy(*to, data);
}

void Config::validateDocument(const rapidjson::Document &document) {
    // log level
    assert(document.HasMember("log_level"));
    assert(document["log_level"].IsInt());

    // camera config
    assert(document.HasMember("camera"));
    assert(document["camera"].IsObject());

    assert(document["camera"].HasMember("host"));
    assert(document["camera"]["host"].IsString());

    assert(document["camera"].HasMember("image_path"));
    assert(document["camera"]["image_path"].IsString());

    assert(document["camera"].HasMember("user"));
    assert(document["camera"]["user"].IsString());

    assert(document["camera"].HasMember("password"));
    assert(document["camera"]["password"].IsString());

    // pms config
    assert(document.HasMember("pms"));
    assert(document["pms"].IsObject());

    assert(document["pms"].HasMember("host"));
    assert(document["pms"]["host"].IsString());

    assert(document["pms"].HasMember("path"));
    assert(document["pms"]["path"].IsString());

    assert(document["pms"].HasMember("user"));
    assert(document["pms"]["user"].IsString());

    assert(document["pms"].HasMember("password"));
    assert(document["pms"]["password"].IsString());
}

Config::~Config() {
    // free camera
    free(this->camera->host);
    free(this->camera->password);
    free(this->camera->image_path);
    free(this->camera->user);
    delete this->camera;

    free(this->pms->host);
    free(this->pms->password);
    free(this->pms->path);
    free(this->pms->user);
    delete this->pms;

    if (this->log_file != nullptr) {
        free(this->log_file);
    }
}
