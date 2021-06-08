rm = del

prog: entity.o main.o
	gcc -o main.exe entity.o main.o -l:pdcurses.a
	$(rm) main.o
	$(rm) entity.o

main.o: main.c
	gcc -c main.c

entity.o: entity.c
	gcc -c entity.c
