TARGET:=main
CROSS:=
CC:=$(CROSS)gcc
ECHO:=@

OBJS+=./src/main.o

CFLAGS+=-I. -I./src
CFLAGS+=-DDEBUG=1
CFLAGS+=-c -O0 -ggdb

CSFLAGS+=$(CFLAGS)
CCFLAGS+=$(CFLAGS) -std=c11
CCPPFLAGS+=$(CFLAGS) -std=c++11

LDFLAGS+=-O0 -ggdb
LDFLAGS+=-L.
LDFLAGS+=-lpthread -lstdc++ -lm -lc
STATIC_LIBS+=

.PHONY:all clean
all:$(TARGET).elf
	@echo -e '[33m[GO] [32m$<[0m'
	$(ECHO)./$<
$(TARGET).elf:$(OBJS) $(STATIC_LIBS)
	@echo -e '[33m[LD] [32m$@[0m'
	$(ECHO)$(CC) -o $@ $^ $(LDFLAGS)
%.o:%.s
	@echo -e '[33m[CC] [32m$@[0m'
	$(ECHO)$(CC) -o $@ $^ $(CSFLAGS)
%.o:%.c
	@echo -e '[33m[CC] [32m$@[0m'
	$(ECHO)$(CC) -o $@ $^ $(CCFLAGS)
%.o:%.cpp
	@echo -e '[33m[CC] [32m$@[0m'
	$(ECHO)$(CC) -o $@ $^ $(CCPPFLAGS)
clean:
	@echo -e '[33m[RM] [32m$(TARGET).elf $(OBJS)[0m'
	$(ECHO)rm -rf $(TARGET).elf $(OBJS)
