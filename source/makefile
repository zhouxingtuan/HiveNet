
JEMALLOC_INC := ../jemalloc/include/jemalloc

OPENSSL_LIB := /usr/local/ssl/lib
OPENSSL_INC := /usr/local/ssl/include

INCLUDES = -I$(OPENSSL_INC) -I$(JEMALLOC_INC)

CFLAGS = -O2 -Wall -pthread $(INCLUDES) -L$(OPENSSL_LIB) -lssl -lcrypto -lstdc++ -std=c++11 -ldl
CC = gcc

OBJS = common.o

all: $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

common.o:common.cpp common.h
