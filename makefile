OBJ 	= main.o mat.o mat_aufruf.o trivia.o trivia_aufruf.o game_rand.o game_rand_aufruf.o  prim.o prim_aufruf.o polynom.o polynom_aufruf.o
TARGET	= Ubung
LINK	= gcc

all: $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -lm -o $(TARGET) $(OBJ)

clean:
	rm *.o $(TARGET)
