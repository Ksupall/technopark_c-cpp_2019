CC := g++
CFLAGS := -std=c++11 -Wall -Werror

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -g3 -ggdb
endif

app.exe : serial_work.o parallel_work.o err_codes.o main.o -pthread
	$(CC) $^ -o $@
	
file.exe : create_file.o
	$(CC) $^ -o $@
	
%.o : %.cpp *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe