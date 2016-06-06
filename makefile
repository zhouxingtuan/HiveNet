
JEMALLOC_STATICLIB := ./jemalloc/lib/libjemalloc_pic.a ./jemalloc/lib/libjemalloc.a
JEMALLOC_INC := ./jemalloc/include/jemalloc

LUAJIT_STATICLIB := ./lua/luajit/src/libluajit.a
LUAJIT_INC := ./lua/luajit/src/

LUASOCKET_STATICLIB := ./lua/luasocket/src/libluasocket.a
LUASOCKET_INC := ./lua/luasocket/src/

LUASQL_STATICLIB := ./lua/luasql/src/libluasql.a
LUASQL_INC := ./lua/luasql/src/

TOLUA_INC := ./lua/tolua/

LUA_SCRIPT_INC := ./lua

HIVENET_STATICLIB := $(JEMALLOC_STATICLIB) $(LUAJIT_STATICLIB) $(LUASQL_STATICLIB) $(LUASOCKET_STATICLIB)

OPENSSL_LIB := /usr/local/ssl/lib
OPENSSL_INC := /usr/local/ssl/include

HIVENET_INC := ./source

# static的依赖库要放在static的后面，比如luasocket依赖openssl
LIBPATH = -L/usr/lib/mysql -L/usr/local/lib -L$(OPENSSL_LIB)
LIBS = -lmysqlclient -levent -lssl -lcrypto

INCLUDES = -I$(LUAJIT_INC) -I$(TOLUA_INC) -I$(OPENSSL_INC) -I$(LUASQL_INC) -I$(LUASOCKET_INC) -I$(LUA_SCRIPT_INC) -I$(HIVENET_INC) -I$(JEMALLOC_INC)

# 注意，这里的 -ldl 需要放在flag的最后才能生效
CFLAGS = -O2 -Wall -pthread -lrt $(INCLUDES) -lstdc++ -std=c++11 $(HIVENET_STATICLIB) $(LIBPATH) $(LIBS) -ldl

CC = gcc
RM = rm -f
BIN =
TARGET = hive-server

export LUA_OBJDIR = ${shell pwd}/lua
export TOLUA_OBJDIR = ${shell pwd}/lua/tolua
export HIVENET_OBJDIR = ${shell pwd}/source

$(TARGET): $(LUA_OBJDIR) $(TOLUA_OBJDIR) $(HIVENET_OBJDIR) main.o
	$(MAKE) -C jemalloc
	$(MAKE) -C lua/luasocket
	$(MAKE) -C lua/luasql
	$(MAKE) -C lua/luajit
	$(MAKE) -C lua/tolua
	$(MAKE) -C lua
	$(MAKE) -C source
	$(CC) -g $(LUA_OBJDIR)/*.o $(TOLUA_OBJDIR)/*.o $(HIVENET_OBJDIR)/*.o main.o -o $(TARGET) $(CFLAGS)

main.o: main.cpp
	$(CC) -g -c $< -o $@ -O2 -Wall -pthread $(INCLUDES) -lstdc++ -std=c++11 -ldl


clean:
	-$(RM) $(LUA_OBJDIR)/*.o
	-$(RM) $(TOLUA_OBJDIR)/*.o
	-$(RM) $(HIVENET_OBJDIR)/*.o
	-$(RM) $(TARGET)
	-$(RM) main.o





