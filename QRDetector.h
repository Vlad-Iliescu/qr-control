#ifndef QR_CONTROL_QRDETECTOR_H
#define QR_CONTROL_QRDETECTOR_H

#include "quirc.h"
#include "image_formats/JPEG.h"

class QRDetector {
private:
    struct quirc *qr;
    uint8_t *image;
    int codes_count = 0;

public:
    QRDetector();

    virtual ~QRDetector();

    void loadFromData(byte *data, const size_t &size);

    int getCodesCount() const;
};


#endif //QR_CONTROL_QRDETECTOR_H
