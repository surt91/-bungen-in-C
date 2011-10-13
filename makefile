OBJ 	= main.o menu.o help.o mat.o mat_aufruf.o trivia.o trivia_aufruf.o\
			game_rand.o game_rand_aufruf.o prim.o prim_aufruf.o conway.o\
			snake.o roulette.o
TARGET	= Ubung
LINK	= gcc
CC		= gcc
CFLAGS	= -march=native -O2 -pipe -fomit-frame-pointer -funroll-all-loops -ffast-math -finline-functions
LFLAGS	= -lm -lcairo -lncurses
#~ WARNLEVEL= -Wall -pedantic
WARNLEVEL= -Wall

all: $(TARGET)

%.o: %.c
	$(CC) -c $(WARNLEVEL) $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm *.o $(TARGET)
