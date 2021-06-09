
linux: entity.o main.o
	gcc -o main entity.o main.o -lcurses
	rm main.o
	rm entity.o

win: entity.o main.o
	gcc -o main.exe entity.o main.o -l:pdcurses.a
	del main.o
	del entity.o

main.o: main.c
	gcc -c main.c -l:pdcurses.a -I./include

entity.o: entity.c
	gcc -c entity.c
