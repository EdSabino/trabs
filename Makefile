all: generate

generate: clean generate_account generate_main
	gcc -o program main.o account.o -g

generate_main: main.c account.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

generate_account: account.c account.h
	gcc -o account.o account.c -c -W -Wall -ansi -pedantic
 
clean:
	rm -rf *.o
	rm -rf *.txt
	rm -rf program
	rm -rf bank.ss