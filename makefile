ONUM	= numeric/mat.o numeric/mat_aufruf.o numeric/runge_kutta.o \
		  numeric/plot_time_series.o numeric/rk4_lorenz.o \
		  numeric/fft.o numeric/n_harm_osz.o \
		  numeric/cellular_automata.o
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
OKRYPTO	= krypto/AES.o

OBJ 	= main.o menu.o help.o \
		  $(ONUM) $(OTRIVIA) $(OZUFALL) $(OPRIM) $(OGAMES) $(OUHR) $(OKRYPTO)

TARGET	= Ubung
LINK	= gcc
CC	= gcc
CFLAGS	= -march=native -O2 -pipe -fomit-frame-pointer -funroll-all-loops -ffast-math -finline-functions
#~ CFLAGS	= -g
LFLAGS	= -lm -lcairo -lncurses
#~ WARNLEVEL= -Wall -pedantic
WARNLEVEL= -Wall

all: $(TARGET)

%.o: %.c %.h
	$(CC) -c $(WARNLEVEL) $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LFLAGS)

clean:
	rm -rf $(OBJ) $(TARGET)
