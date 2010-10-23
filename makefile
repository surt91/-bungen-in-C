OBJ = main.o functions.o
TARGET	= Ubung
LINK	= gcc
CC = gcc

all: $(TARGET)

functions.o: functions.c functions.h
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -lm -o $(TARGET) $(OBJ)

clean:
	rm *.o $(TARGET)
