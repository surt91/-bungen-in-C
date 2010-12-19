OBJ 	= main.o functions.o
TARGET	= Ubung
LINK	= gcc

all: $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -lm -o $(TARGET) $(OBJ)

clean:
	rm *.o $(TARGET)
