
JEMALLOC_INC := ./../jemalloc/include/jemalloc

OPENSSL_LIB := /usr/local/ssl/lib
OPENSSL_INC := /usr/local/ssl/include

LUASOCKET_STATICLIB := ./luasocket/src/libluasocket.a
LUASOCKET_INC := ./luasocket/src/

LUASQL_STATICLIB := ./luasql/src/libluasql.a
LUASQL_INC := ./luasql/src/

HIVENET_INC := ./../source

INCLUDES = -I$(OPENSSL_INC) -I$(LUASOCKET_INC) -I$(LUASQL_INC) -I$(JEMALLOC_INC) -I$(HIVENET_INC)

CFLAGS = -O2 -Wall -pthread $(INCLUDES) -L$(OPENSSL_LIB) -L$(LUASOCKET_STATICLIB) -L$(LUASQL_STATICLIB) -lssl -lcrypto -lstdc++ -std=c++11 -ldl
CC = gcc

OBJS = script.o scriptmanager.o hivenet.o

all: $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) -g -c $< -o $@ $(CFLAGS)

script.o:script.cpp script.h ../source/handlerinterface.h

scriptmanager.o:script.o scriptmanager.cpp scriptmanager.h

#manual.o:manual.hpp
#	$(CC) -g -c $< -o $@ $(CFLAGS)

hivenet.o:$(OBJS) manual.hpp hivenet.cpp ../source/hivenet.h



