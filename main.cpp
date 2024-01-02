#include <iostream>
#include "Request.h"
#include "Config.h"
#include "quirc.h"

int main() {
    auto *config = new Config("config.json");

    auto *request = new Request();
    request->setUsername(config->camera->user);
    request->setPassword(config->camera->password);
    request->setHost(config->camera->host);
    request->setDebug(config->log_level == 7);

    Response response;

//    FILE *f = fopen("current.jpg", "wb");
//    request->get("/record/current.jpg", f);
    response = request->get(config->camera->image_path);
//    fwrite(response.data, sizeof(byte), response.size, f);


    struct quirc *qr;
    qr = quirc_new();
    if (!qr) {
        perror("Failed to allocate memory");
        abort();
    }

    if (quirc_resize(qr, 640, 480) < 0) {
        perror("Failed to allocate video memory");
        abort();
    }

    uint8_t *image;
    int w, h;

    image = quirc_begin(qr, &w, &h);
    memcpy(image, response.data, response.size);

    int num_codes;
    num_codes = quirc_count(qr);
    std::cout << "CODES = " << num_codes << std::endl;

    quirc_end(qr);

    quirc_destroy(qr);

    auto *request2 = new Request();
    request2->setDebug(config->log_level == 7);
    request2->setHost(config->pms->host);

    response = request2->post(config->pms->path, response.data, response.size);

    std::cout << "ENDING! " << std::endl
              << config->pms->host << std::endl
              << config->pms->path << std::endl
              << request->isInitOk() << std::endl
              << response.http_code << std::endl
              << std::endl;

    return 0;
}
