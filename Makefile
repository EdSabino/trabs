all: run

run: generate
	./program

generate: clean generate_main
	gcc -o program main.o -g

generate_main: main.c
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic
 
clean:
	rm -rf *.o
	rm -rf *.txt
	rm -rf program
	rm -rf banks/*
	mkdir banks/index
	mkdir banks/files
