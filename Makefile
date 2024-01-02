# Environment
CC=g++
LIBS = -lcurl -lpthread -lm -ldl
CFLAGS = -g -std=c++0x ${LIBS} -O3

# Dependencies
DEPS = main.h Config.h Response.h Request.h
OBJ = tmp/main.o tmp/Config.o tmp/Response.o tmp/Request.o

# Script to run before the make starts
PRE_MAKE:=$(shell mkdir -p tmp > /dev/null)

# how to buils tmp/*.o objects for *.c files
tmp/%.o: %.cpp $(DEPS)
	$(CC) -c -Wall -w -o $@ $< $(CFLAGS)

qr_control: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf qr_control tmp
