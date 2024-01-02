#define HAVE_PROTOTYPES

#include <cstdint>
#include <iostream>
#include <jpeglib.h>
#include <stdexcept>
#include <iostream>

typedef unsigned char byte;

void jpegErrorExit(j_common_ptr cinfo);

void decode(byte *data, unsigned int size);