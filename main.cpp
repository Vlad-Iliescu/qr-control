#include <iostream>
#include "Request.h"
#include "Config.h"
#include "QRDetector.h"
#include "log_handlers/ConsoleHandler.h"
#include "log_handlers/FileHandler.h"

int main() {
    auto *config = new Config("config.json");

    auto *logger = new Logger(static_cast<LogLevel>(config->log_level));
    if (config->log_file != nullptr) {
        logger->addHandlers(new FileHandler(config->log_file));
    }
    if (config->log_console) {
        logger->addHandlers(new ConsoleHandler());
    }

    auto *request = new Request(logger);
    request->setUsername(config->camera->user);
    request->setPassword(config->camera->password);
    request->setHost(config->camera->host);
    request->setDebug(config->log_level == 7);

    Response response = request->get(config->camera->image_path);
    delete request;

    auto *decoder = new QRDetector(logger);
    decoder->loadFromData(response.data, response.size);

    QR *codes = decoder->getCodes();
    for (int i = 0; i < decoder->getCodesCount(); ++i) {
        std::cout << "QR[" << i << "]= " << std::endl
                  << codes[i].payload << std::endl
                  << codes[i].x << std::endl
                  << codes[i].y << std::endl
                  << codes[i].size << std::endl;
    }

    auto *request2 = new Request(logger);
    request2->setDebug(config->log_level == 7);
    request2->setHost(config->pms->host);
    response = request2->post(config->pms->path, response.data, response.size);
    delete request2;

    std::cout << "ENDING! " << std::endl;

    return 0;
}
