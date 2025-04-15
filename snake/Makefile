CFLAGS=-std=c99 -Wall -g

all: game

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm *.o
	rm game

game: main.o world.o snake.o
	gcc -rdynamic -g main.o world.o snake.o -lcurses -lm -o game

