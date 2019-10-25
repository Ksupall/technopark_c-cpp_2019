CC := gcc
CFLAGS := -std=c11 -Wall -Werror

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -g3 -ggdb
endif

app.exe : serial_work.o main.o
	$(CC) $^ -o $@
	
file.exe : create_file.o
	$(CC) $^ -o $@
	
%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe