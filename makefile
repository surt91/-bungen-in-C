OLINA	= lina/mat.o lina/mat_aufruf.o
OTRIVIA	= trivia/trivia.o trivia/trivia_aufruf.o trivia/benchmark.o
OUHR	= trivia/bin_uhr.o
OZUFALL	= zufall/random.o zufall/random_aufruf.o
OPRIM	= prim/prim.o prim/prim_aufruf.o
OPOLY	= trivia/polynom.o trivia/polynom_aufruf.o
OGAMES	= games/highscore.o\
		  games/conway.o games/snake.o games/roulette.o\
		  games/vier_gewinnt.o\
		  games/karten/karten.o\
		  games/karten/poker.o games/karten/blackjack.o

OBJ 	= main.o menu.o help.o \
		  $(OLINA) $(OTRIVIA) $(OZUFALL) $(OPRIM) $(OGAMES) $(OUHR)

TARGET	= Ubung
LINK	= gcc
CC		= gcc
CFLAGS	= -march=native -O2 -pipe -fomit-frame-pointer -funroll-all-loops -ffast-math -finline-functions
LFLAGS	= -lm -lcairo -lncursesw
#~ WARNLEVEL= -Wall -pedantic
WARNLEVEL= -Wall

all: $(TARGET)

%.o: %.c %.h
	$(CC) -c $(WARNLEVEL) $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -rf $(OBJ) $(TARGET)
