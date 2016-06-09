
JEMALLOC_INC := ../jemalloc/include/jemalloc

OPENSSL_LIB := /usr/local/ssl/lib
OPENSSL_INC := /usr/local/ssl/include

INCLUDES = -I$(OPENSSL_INC) -I$(JEMALLOC_INC)

CFLAGS = -O2 -Wall -pthread $(INCLUDES) -L$(OPENSSL_LIB) -lssl -lcrypto -lstdc++ -std=c++11 -ldl
CC = gcc

DEBUG= -g -ggdb

OBJS = common.o buffer.o packet.o taskinterface.o handlerinterface.o worker.o handlerqueue.o accept.o client.o epoll.o

all: $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) $(DEBUG) -c $< -o $@ $(CFLAGS)

common.o:common.cpp common.h

buffer.o:common.o buffer.cpp buffer.h

packet.o:buffer.o packet.cpp packet.h

taskinterface.o:common.o taskinterface.cpp taskinterface.h

handlerinterface.o:packet.o taskinterface.o handlerinterface.cpp handlerinterface.h

worker.o:handlerinterface.o worker.cpp worker.h

handlerqueue.o:worker.o handlerinterface.o handlerqueue.cpp handlerqueue.h

accept.o:packet.o accept.cpp accept.h

client.o:accept.o client.cpp client.h

epoll.o:client.o epoll.cpp epoll.h
