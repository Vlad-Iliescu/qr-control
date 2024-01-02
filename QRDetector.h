#ifndef QR_CONTROL_QRDETECTOR_H
#define QR_CONTROL_QRDETECTOR_H

#include "quirc.h"
#include "image_formats/JPEG.h"

typedef struct {
    char *payload;
    int x;
    int y;
    int size;
    bool error;
} QR;

class QRDetector {
private:
    struct quirc *qr;
    uint8_t *image;
    int codes_count = 0;
    QR *codes = nullptr;

public:
    QRDetector();

    virtual ~QRDetector();

    void loadFromData(byte *data, const size_t &size);

    int getCodesCount() const;

    QR *getCodes() const;

    QR getCode(int i) const;
};


#endif //QR_CONTROL_QRDETECTOR_H
