all: main.o editor.o
	gcc -o editor main.o editor.o -lncurses

main.o: main.c editor.h
	gcc -c main.c

editor.o: editor.c editor.h
	gcc -c editor.c

clean:
	rm *.o
	rm editor

run:
	make
	./editor test.txt