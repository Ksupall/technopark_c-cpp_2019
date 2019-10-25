CC := g++
CFLAGS := -std=c++11 -Wall -Werror -pthread

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -g3 -ggdb
endif

app.exe : serial_work.o parallel_work.o main.o
	$(CC) $^ -o $@
	
file.exe : create_file.o
	$(CC) $^ -o $@
	
%.o : %.cpp *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe