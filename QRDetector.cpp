#include <cstring>
#include "QRDetector.h"

QRDetector::QRDetector() {
    this->qr = quirc_new();
    if (!this->qr) {
        perror("Failed to allocate memory");
        abort();
    }
}

QRDetector::~QRDetector() {
    quirc_destroy(this->qr);
}

void QRDetector::loadFromData(byte *data, const size_t &size) {
    auto *jpeg = new JPEG(data, size);

    std::cout << "size: " << jpeg->getWidth() << "x" << jpeg->getHeight() << std::endl;

    int rc = quirc_resize(qr, jpeg->getWidth(), jpeg->getHeight());
    std::cout << "qr res: " << rc << std::endl;

    this->image = quirc_begin(qr, nullptr, nullptr);
    jpeg->fillDecompressedBuffer(image);

    quirc_end(this->qr);
    this->codes_count = quirc_count(this->qr);
    std::cout << "CODES = " << this->codes_count << std::endl;

    this->codes = new QR[this->codes_count];
    for (int i = 0; i < this->codes_count; i++) {
        struct quirc_code code;
        struct quirc_data data;
        quirc_decode_error_t err;

        quirc_extract(this->qr, i, &code);

        /* Decoding stage */
        err = quirc_decode(&code, &data);
        if (err) {
            std::cout << "DECODE FAILED: " << quirc_strerror(err) << std::endl;
        } else {
            std::cout << "Data: " << data.payload << std::endl;
            this->codes[i].payload = static_cast<char *>(malloc(static_cast<size_t>(data.payload_len)));
            memcpy(this->codes[i].payload, data.payload, static_cast<size_t>(data.payload_len));
            this->codes[i].x = code.corners->x;
            this->codes[i].y = code.corners->y;
            this->codes[i].size = code.size;
        }

        std::cout << "Corcers: x=" << code.corners->x << ", y=" << code.corners->y << ", size=" << code.size
                  << std::endl;
    }
}

int QRDetector::getCodesCount() const {
    return codes_count;
}

QR *QRDetector::getCodes() const {
    return codes;
}

QR QRDetector::getCode(int i) const {
    return codes[i];
}
