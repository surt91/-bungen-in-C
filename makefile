OBJ 	= main.o functions.o mat.o mataufruf.o
TARGET	= Ubung
LINK	= gcc

all: $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -lm -o $(TARGET) $(OBJ)

clean:
	rm *.o $(TARGET)
