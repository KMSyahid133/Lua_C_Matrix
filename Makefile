CC = gcc
OFLAG = -c -fPIC -Wall -O2 -shared
DLLFLAG = ./Lua_Header/lua54.dll -O2 -Wall -shared

OBJPATH =./Objects

SRCS = $(wildcard ./C_Matrix/*.c)
HEADSRCS = $(wildcard ./C_Matrix/*.h)
OBJS = $(patsubst ./C_Matrix/%.c, ./Objects/%.o, $(SRCS))
OBJECTS = $(wildcard ./Objects/*.o)

INTERFACE = ./matrix_lua_interface.c
LUAHEADER = ./Lua_Header/lua_header.h
INTERFACEOBJ = ./Objects/interface.o

all: $(OBJS) $(INTERFACEOBJ) dll
# black magic fuckery
./Objects/%.o: ./C_Matrix/%.c
	$(CC) $(OFLAG) $< -o $@

$(INTERFACEOBJ): $(INTERFACE) $(LUAHEADER) $(HEADSRCS) 
	$(CC) $(OFLAG) $< -o $(OBJPATH)/$(INTERFACEOBJ)
	

dll: $(OBJS) $(INTERFACEOBJ) $(LUAHEADER) $(HEADSRCS)
	$(CC) $(OBJS) $(INTERFACEOBJ) $(DLLFLAG) -o matrix.dll

.PHONY: clean

clean:
	rm ./Objects/*.o
