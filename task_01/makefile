CC := g++

CFLAGS := -std=c11 -Wall

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

ifeq ($(mode), debug)
	CFLAGS += -g3 -ggdb
endif

app.exe : struct.o main.o
	$(CC) $^ -o $@	
	
%.o : %.cpp *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe