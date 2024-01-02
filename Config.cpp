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

    // read camera settings
    this->readString(&this->camera->host, document["camera"]["host"].GetStringLength(),
                     document["camera"]["host"].GetString());
    this->readString(&this->camera->image_path, document["camera"]["image_path"].GetStringLength(),
                     document["camera"]["image_path"].GetString());
    this->readString(&this->camera->user, document["camera"]["user"].GetStringLength(),
                     document["camera"]["user"].GetString());
    this->readString(&this->camera->password, document["camera"]["password"].GetStringLength(),
                     document["camera"]["password"].GetString());

    // cleanup
    free(buffer);
}

void Config::readString(char **to, size_t size, const char *data) {
    *to = static_cast<char *>(calloc(size + 1, sizeof(char)));
    strcpy(*to, data);
}

void Config::validateDocument(const rapidjson::Document &document) {
    assert(document.HasMember("log_level"));
    assert(document["log_level"].IsInt());

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
}
