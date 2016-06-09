
JEMALLOC_INC := ./../jemalloc/include/jemalloc

OPENSSL_LIB := /usr/local/ssl/lib
OPENSSL_INC := /usr/local/ssl/include

LUASOCKET_STATICLIB := ./luasocket/src/libluasocket.a
LUASOCKET_INC := ./luasocket/src/

LUASQL_STATICLIB := ./luasql/src/libluasql.a
LUASQL_INC := ./luasql/src/

LUAHIREDIS_STATICLIB := ./luahiredis/libhiredis.a
LUAHIREDIS_INC := ./luahiredis/

HIVENET_INC := ./../source

INCLUDES = -I$(OPENSSL_INC) -I$(LUASOCKET_INC) -I$(LUASQL_INC) -I$(LUAHIREDIS_INC) -I$(JEMALLOC_INC) -I$(HIVENET_INC)

CFLAGS = -O2 -Wall -pthread $(INCLUDES) -L$(OPENSSL_LIB) -L$(LUASOCKET_STATICLIB) -L$(LUASQL_STATICLIB) -L$(LUAHIREDIS_STATICLIB) -lssl -lcrypto -lstdc++ -std=c++11 -ldl
CC = gcc

DEBUG= -g -ggdb

OBJS = script.o scriptmanager.o hivenet.o

all: $(OBJS)

$(OBJS): %.o:%.cpp
	$(CC) $(DEBUG) -c $< -o $@ $(CFLAGS)

script.o:script.cpp script.h ../source/handlerinterface.h

scriptmanager.o:script.o scriptmanager.cpp scriptmanager.h

#manual.o:manual.hpp
#	$(CC) $(DEBUG) -c $< -o $@ $(CFLAGS)

hivenet.o:$(OBJS) manual.hpp hivenet.cpp ../source/hivenet.h



