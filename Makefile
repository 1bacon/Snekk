
flags = -Wno-discarded-qualifiers -Wall -I./include

linux: main
	rm *.o

win: main.exe
	del *.o

main: states.o entity.o world.o main.o
	gcc -o main states.o entity.o world.o main.o -l:pdcurses.a $(flags)

main.exe: states.o entity.o world.o main.o 
	gcc -o main.exe states.o entity.o world.o main.o -l:pdcurses.a $(flags)

main.o: main.c
	gcc -c main.c -l:pdcurses.a $(flags)

entity.o: entity.c
	gcc -c entity.c $(flags)

world.o: world.c
	gcc -c world.c $(flags)

states.o: states.c
	gcc -c states.c $(flags)