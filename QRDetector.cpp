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
}

int QRDetector::getCodesCount() const {
    return codes_count;
}
