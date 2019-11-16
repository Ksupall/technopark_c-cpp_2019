CC := gcc
CFLAGS := -std=c11 -Wall -Werror
OBJ := serial_work.o parallel_work.o
CFILES := serial_work.c parallel_work.c

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -g3 -ggdb
endif

app.exe : main.o
	$(CC) $^ -o $@
	
lib_dyn : $(CFILES)
	$(CC) $(CFLAGS) -D T -D ARR_EXPORTS -c $^
	$(CC) -shared $(OBJ) -Wl,--subsystem,windows -o lib.dll
	
%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe *dll