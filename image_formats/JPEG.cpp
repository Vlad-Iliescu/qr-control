#include "JPEG.h"

JPEG::JPEG(Logger *logger, byte *data, const size_t &size) : size(size), data(data), logger(logger) {
    this->getLogger()->info("starting decompression.");
    this->dinfo = new jpeg_decompress_struct();
    this->jerr = new jpeg_error_mgr();
    this->dinfo->err = JPEG::my_error_mgr(this->jerr);
    this->startDecompressing();
}

byte *JPEG::getData() const {
    return data;
}

size_t JPEG::getSize() const {
    return size;
}

bool JPEG::fillDecompressedBuffer(uint8_t *image) {
    if (!this->isDecompressionSuccess()) {
        return false;
    }

    for (int y = 0; y < this->getHeight(); y++) {
        auto row_pointer = reinterpret_cast<JSAMPROW>(image + y * this->getWidth());

        jpeg_read_scanlines(this->dinfo, &row_pointer, 1);
    }

    return true;
}

void JPEG::startDecompressing() {

    int rc;

    // init decompression
    jpeg_create_decompress(this->dinfo);

    // feed source
    jpeg_mem_src(this->dinfo, this->getData(), this->getSize());

    // read header
    rc = jpeg_read_header(this->dinfo, TRUE);
    if (!rc) {
        logger->warning("Could not ");
        jpeg_destroy_decompress(this->dinfo);
        return;
    }

    this->_header_read = true;

    // starting decompression
    this->dinfo->output_components = 1;
    this->dinfo->out_color_space = JCS_GRAYSCALE;
    rc = jpeg_start_decompress(this->dinfo);
    std::cout << "dec: " << rc << std::endl;

    if (!rc) {
        jpeg_finish_decompress(this->dinfo);
        jpeg_destroy_decompress(this->dinfo);
        return;
    }
    this->_decompression_started = true;

    // count components
    if (this->dinfo->output_components != 1) {
        std::cout << "Unexpected number of output components: " << this->dinfo->output_components << std::endl;
        jpeg_finish_decompress(this->dinfo);
        jpeg_destroy_decompress(this->dinfo);
        return;
    }
    this->_correct_components_count = true;

}

unsigned int JPEG::getWidth() {
    return this->dinfo->output_width;
}

unsigned int JPEG::getHeight() {
    return this->dinfo->output_height;
}

JPEG::~JPEG() {
    if (this->_decompression_started) {
        jpeg_finish_decompress(this->dinfo);
    }
    jpeg_destroy_decompress(this->dinfo);

    delete (this->dinfo);
    delete (this->jerr);
}

bool JPEG::isDecompressionSuccess() {
    return this->_header_read && this->_decompression_started && this->_correct_components_count;
}

struct jpeg_error_mgr *JPEG::my_error_mgr(struct jpeg_error_mgr *err) {
    jpeg_std_error(err);

    err->error_exit = JPEG::my_error_exit;
    err->output_message = JPEG::my_output_message;

    return err;
}

void JPEG::my_error_exit(struct jpeg_common_struct *com) {
    std::cout << "my_error_exit: " << com->err->msg_code << std::endl;
    JPEG::my_output_message(com);
    //todo: recover: continue from here somehow
    exit(1);
}

void JPEG::my_output_message(struct jpeg_common_struct *com) {
    std::cout << "my_output_message: ";

    char buf[JMSG_LENGTH_MAX];

    com->err->format_message(com, buf);
    std::cout << buf << std::endl;
}

void JPEG::setLogger(Logger *logger) {
    this->logger = logger;
}

Logger *JPEG::getLogger() const {
    return logger;
}
