
JEMALLOC_INC := ../jemalloc/include/jemalloc

OPENSSL_LIB := /usr/local/ssl/lib
OPENSSL_INC := /usr/local/ssl/include

INCLUDES = -I$(OPENSSL_INC) -I$(JEMALLOC_INC)

CFLAGS = -O2 -Wall -pthread $(INCLUDES) -L$(OPENSSL_LIB) -lssl -lcrypto -lstdc++ -std=c++11 -ldl
CC = gcc

OBJS = common.o buffer.o packet.o worker.o taskqueue.o taskupdate.o

all: $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) -g -c $< -o $@ $(CFLAGS)

common.o:common.cpp common.h

buffer.o:common.o buffer.cpp buffer.h

packet.o:buffer.o packet.cpp packet.h

worker.o:common.o worker.cpp worker.h taskinterface.h

taskqueue.o:worker.o taskqueue.cpp taskqueue.h taskinterface.h

taskupdate.o:common.o taskupdate.cpp taskupdate.h taskinterface.h handlerinterface.h
