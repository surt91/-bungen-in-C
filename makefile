OBJ 	= main.o menu.o help.o mat.o mat_aufruf.o trivia.o trivia_aufruf.o game_rand.o game_rand_aufruf.o  prim.o prim_aufruf.o polynom.o polynom_aufruf.o
TARGET	= Ubung
LINK	= gcc
CC		= gcc
CFLAGS	= -march=native -O2 -pipe -fomit-frame-pointer -funroll-all-loops -ffast-math -finline-functions
#WARNLEVEL= -Wall -pedantic

all: $(TARGET)

%.o: %.c
	$(CC) -c $(WARNLEVEL) $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -lm -o $(TARGET) $(OBJ)

clean:
	rm *.o $(TARGET)
