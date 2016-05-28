
JEMALLOC_INC := ./../jemalloc/include/jemalloc

OPENSSL_LIB := /usr/local/ssl/lib
OPENSSL_INC := /usr/local/ssl/include

HIVENET_INC := ./../source

INCLUDES = -I$(OPENSSL_INC) -I$(JEMALLOC_INC) -I$(HIVENET_INC)

CFLAGS = -O2 -Wall -pthread $(INCLUDES) -L$(OPENSSL_LIB) -lssl -lcrypto -lstdc++ -std=c++11 -ldl
CC = gcc

OBJS = hivenet.o

all: $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) -g -c $< -o $@ $(CFLAGS)

hivenet.o:hivenet.cpp ../source/hivenet.h
