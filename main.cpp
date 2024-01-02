#include <iostream>
#include "Request.h"
#include "Config.h"
#include "QRDetector.h"

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

    auto *decoder = new QRDetector();
    decoder->loadFromData(response.data, response.size);

//    struct quirc *qr;
//    qr = quirc_new();
//    if (!qr) {
//        perror("Failed to allocate memory");
//        abort();
//    }

//    if (quirc_resize(qr, 640, 480) < 0) {
//        perror("Failed to allocate video memory");
//        abort();
//    }

//    uint8_t *image;
//    int w, h, rc;

//    image = quirc_begin(qr, &w, &h);

//    auto *jpeg = new JPEG(response.data, response.size);

//    std::cout << "size: " << jpeg->getWidth() << "x" << jpeg->getHeight() << std::endl;

//    rc = quirc_resize(qr, jpeg->getWidth(), jpeg->getHeight());
//    std::cout << "qr res: " << rc << std::endl;

//    image = quirc_begin(qr, nullptr, nullptr);
//    jpeg->fillDecompressedBuffer(image);

//    quirc_end(qr);
//    int num_codes;
//    num_codes = quirc_count(qr);
//    std::cout << "CODES = " << num_codes << std::endl;

//    for (int i = 0; i < num_codes; i++) {
//        struct quirc_code code;
//        struct quirc_data data;
//        quirc_decode_error_t err;
//
//        quirc_extract(qr, i, &code);
//
//        /* Decoding stage */
//        err = quirc_decode(&code, &data);
//        if (err)
//            std::cout << "DECODE FAILED: " << quirc_strerror(err) << std::endl;
//        else
//            std::cout << "Data: " << std::endl << data.payload << std::endl;
//        std::cout << "Corcers: x=" << code.corners->x << ", y=" << code.corners->y << ", size=" << code.size
//                  << std::endl;
//    }
//
//
//    quirc_destroy(qr);


//    struct jpeg_decompress_struct dinfo;
//    struct jpeg_error_mgr jerr;
//    dinfo.err = jpeg_std_error(&jerr);
//    int rc;

//    jpeg_create_decompress(&dinfo);
//    std::cout << "create: " << std::endl;

//    jpeg_mem_src(&dinfo, response.data, response.size);
//    std::cout << "mem: " << std::endl;

//    rc = jpeg_read_header(&dinfo, TRUE);
//    std::cout << "header: " << rc << std::endl;

//    dinfo.output_components = 1;
//    dinfo.out_color_space = JCS_GRAYSCALE;
//    rc = jpeg_start_decompress(&dinfo);
//    std::cout << "dec: " << rc << std::endl;

//    if (dinfo.output_components != 1) {
//        std::cout << "Unexpected number of output components: " << dinfo.output_components << std::endl;
//    }

//    std::cout << "size: " << dinfo.output_width << "x" << dinfo.output_height << std::endl;

//    rc = quirc_resize(qr, dinfo.output_width, dinfo.output_height);
//    std::cout << "qr res: " << rc << std::endl;
//
//    image = quirc_begin(qr, nullptr, nullptr);
//
//    for (int y = 0; y < dinfo.output_height; y++) {
//        auto row_pointer = reinterpret_cast<JSAMPROW>(image + y * dinfo.output_width);
//
//        jpeg_read_scanlines(&dinfo, &row_pointer, 1);
//    }
//
//    jpeg_finish_decompress(&dinfo);
//    jpeg_destroy_decompress(&dinfo);
//
//    quirc_end(qr);
//
////    memcpy(image, response.data, response.size);
//
//    int num_codes;
//    num_codes = quirc_count(qr);
//    std::cout << "CODES = " << num_codes << std::endl;
//
//    for (int i = 0; i < num_codes; i++) {
//        struct quirc_code code;
//        struct quirc_data data;
//        quirc_decode_error_t err;
//
//        quirc_extract(qr, i, &code);
//
//        /* Decoding stage */
//        err = quirc_decode(&code, &data);
//        if (err)
//            std::cout << "DECODE FAILED: " << quirc_strerror(err) << std::endl;
//        else
//            std::cout << "Data: " << data.payload << std::endl;
//        std::cout << "Corcers: x=" << code.corners->x << ", y=" << code.corners->y << ", size=" << code.size
//                  << std::endl;
//    }
//
//
//    quirc_destroy(qr);

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
