#ifndef QR_CONTROL_JPEG_H
#define QR_CONTROL_JPEG_H

#define HAVE_PROTOTYPES

#include <cstdint>
#include <iostream>
#include <jpeglib.h>
#include <csetjmp>
#include "../Logger.h"

typedef unsigned char byte;

typedef struct jpegErrorManager {
    /* "public" fields */
    struct jpeg_error_mgr pub;
    /* for return to caller */
    jmp_buf setjmp_buffer;
} JpegError;


class JPEG {
private:
    byte *data;
    size_t size;

    bool _header_read = false;
    bool _decompression_started = false;
    bool _correct_components_count = false;

    struct jpeg_decompress_struct *dinfo;
    struct jpeg_error_mgr *jerr;

    void startDecompressing();

    Logger *logger;

public:
    static void my_output_message(struct jpeg_common_struct *com);

    static void my_error_exit(struct jpeg_common_struct *com);

    static struct jpeg_error_mgr *my_error_mgr(struct jpeg_error_mgr *err);

    JPEG(Logger *logger, byte *data, const size_t &size);

    virtual ~JPEG();

    bool isDecompressionSuccess();

    byte *getData() const;

    size_t getSize() const;

    unsigned int getWidth();

    unsigned int getHeight();

    bool fillDecompressedBuffer(uint8_t *image);

    void setLogger(Logger *logger);

    Logger *getLogger() const;
};


#endif //QR_CONTROL_JPEG_H
