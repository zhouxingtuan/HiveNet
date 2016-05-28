
JEMALLOC_INC := ../jemalloc/include/jemalloc

OPENSSL_LIB := /usr/local/ssl/lib
OPENSSL_INC := /usr/local/ssl/include

INCLUDES = -I$(OPENSSL_INC) -I$(JEMALLOC_INC)

CFLAGS = -O2 -Wall -pthread $(INCLUDES) -L$(OPENSSL_LIB) -lssl -lcrypto -lstdc++ -std=c++11 -ldl
CC = gcc

OBJS = common.o buffer.o packet.o

all: $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) -g -c $< -o $@ $(CFLAGS)

common.o:common.cpp common.h

buffer.o:common.o buffer.cpp buffer.h

packet.o:buffer.o packet.cpp packet.h
