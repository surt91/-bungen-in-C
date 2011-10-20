OBJ 	= main.o menu.o help.o lina/mat.o lina/mat_aufruf.o trivia/trivia.o trivia/trivia_aufruf.o\
			zufall/random.o zufall/random_aufruf.o prim/prim.o prim/prim_aufruf.o games/conway.o\
			games/snake.o games/roulette.o games/karten/karten.o games/karten/poker.o games/karten/blackjack.o trivia/benchmark.o
TARGET	= Ubung
LINK	= gcc
CC		= gcc
CFLAGS	= -march=native -O2 -pipe -fomit-frame-pointer -funroll-all-loops -ffast-math -finline-functions
LFLAGS	= -lm -lcairo -lncurses
#~ WARNLEVEL= -Wall -pedantic
WARNLEVEL= -Wall

all: $(TARGET)

%.o: %.c %.h
	$(CC) -c $(WARNLEVEL) $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -rf $(OBJ) $(TARGET)
