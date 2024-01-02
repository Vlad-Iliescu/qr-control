#include <iostream>
#include "Request.h"
#include "Config.h"

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

    auto *request2 = new Request();
    request2->setDebug(config->log_level == 7);
    request2->setHost("http://192.168.1.20:8989");

    response = request2->post("/upload", response.data, response.size);

    std::cout << "ENDING! " << std::endl
              << config->log_level << std::endl
              << request->isInitOk() << std::endl
              << response.http_code << std::endl
              << std::endl;

    return 0;
}
