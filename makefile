#CC=gcc
#
#all: uebung
#
#uebung: main.o
#	$(CC) main.o -o uebung
#main.o: main.c main.h
#	$(CC) main.c
#clean:
#	rm -rf *o hello

OBJ = main.o functions.o
TARGET	= Ubung
LINK	= gcc

all: $(TARGET)

functions.o: functions.c functions.h
	$(CC) -c $(CCFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -lm -o $(TARGET) $(OBJ)

clean:
	rm *.o $(TARGET)
