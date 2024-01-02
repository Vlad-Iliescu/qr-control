#include "jpeg_with_exception.h"

extern "C" {
#include <jpeglib.h>
}

#include <csetjmp>
#include <cstdio>
#include <cstdlib>

struct jpegErrorManager {
    /* "public" fields */
    struct jpeg_error_mgr pub;
    /* for return to caller */
    jmp_buf setjmp_buffer;
};

char jpegLastErrorMsg[JMSG_LENGTH_MAX];

void jpegErrorExit(j_common_ptr cinfo) {
    /* cinfo->err actually points to a jpegErrorManager struct */
    jpegErrorManager *myerr = (jpegErrorManager *) cinfo->err;
    /* note : *(cinfo->err) is now equivalent to myerr->pub */

    /* output_message is a method to print an error message */
    /*(* (cinfo->err->output_message) ) (cinfo);*/

    /* Create the message */
    (*(cinfo->err->format_message))(cinfo, jpegLastErrorMsg);

    /* Jump to the setjmp point */
    longjmp(myerr->setjmp_buffer, 1);

}