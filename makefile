CC = g++
CFLAGS = -g
TARGET = statSem
HEADER = semantics.h parser.h scanner.h token.h
OBJS = main.c parser.c scanner.cpp semantics.cpp
.SUFFIXIES: .c .o

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
.c.o:	$(HEADER)
	$(CC) $(CFLAGS) -c $<
clean:
	/bin/rm -f *.o $(TARGET)
