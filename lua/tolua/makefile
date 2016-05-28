
LUAJIT_STATICLIB := ../luajit/src/libluajit.a
LUAJIT_INC := ../luajit/src/

INCLUDES = -I$(LUAJIT_INC)
STATICLIB := $(LUAJIT_STATICLIB)

CFLAGS = -O2 -Wall $(INCLUDES) -lstdc++ $(STATICLIB)
CC = gcc

OBJS= tolua_event.o tolua_is.o tolua_to.o tolua_map.o tolua_push.o

all: $(OBJS)

$(OBJS): %.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

tolua_event.o:tolua_event.c tolua_event.h tolua++.h

tolua_is.o:tolua_is.c tolua++.h

tolua_to.o:tolua_to.c tolua++.h

tolua_map.o:tolua_map.c tolua_event.o tolua++.h

tolua_push.o:tolua_push.c tolua++.h






















