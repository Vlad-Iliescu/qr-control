# Environment
CC=g++
QUIRC_SO_PATH = /opt/qr-control/quirc
LIBS = -lcurl -lquirc -ljpeg
CFLAGS = -g -std=c++0x -L${QUIRC_SO_PATH} ${LIBS} -O3

# Dependencies
DEPS = \
    log_handlers/LogHandler.h \
    log_handlers/FileHandler.h \
    log_handlers/ConsoleHandler.h \
    Logger.h \
    Config.h \
    Response.h \
    Request.h \
    image_formats/JPEG.h \
    image_formats/jpeg_with_exception.h \
    QRDetector.h \
    main.h

OBJ = \
    tmp/log_handlers/LogHandler.o \
    tmp/log_handlers/FileHandler.o \
    tmp/log_handlers/ConsoleHandler.o \
    tmp/Logger.o \
    tmp/Config.o \
    tmp/Response.o \
    tmp/Request.o \
    tmp/image_formats/JPEG.o \
    tmp/image_formats/jpeg_with_exception.o \
    tmp/QRDetector.o \
    tmp/main.o

# Script to run before the make starts
PRE_MAKE:=$(shell mkdir -p tmp/image_formats > /dev/null) $(shell mkdir -p tmp/log_handlers > /dev/null)

# how to buils tmp/*.o objects for *.c files
tmp/%.o: %.cpp $(DEPS)
	$(CC) -c -Wall -w -o $@ $< $(CFLAGS)

qr_control: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf qr_control tmp
