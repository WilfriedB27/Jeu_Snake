CC=gcc
CFLAGS=-ansi -pedantic -lgraph

all:Jeux

run:Jeux
	./Jeux

Jeux:main.o scene.o timer_score_menu.o 
	$(CC) $(CFLAGS) -o Jeux main.o scene.o timer_score_menu.o 

main.o:main.c fonction.h
	$(CC) -c main.c $(CFLAGS)

scene.o:scene.c fonction.h
	$(CC) -c scene.c $(CFLAGS)

timer.o:timer_score_menu.c fonction.h
	$(CC) -c timer_score_menu.c $(CFLAGS)

clean:-rm -f *.o Jeux
