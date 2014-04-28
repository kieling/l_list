//CC = gcc -std=c99
//CFLAGS = -Wall
//LDFLAGS = -g


linkedListTest.exe: linkedList.o linkedListTest.o
		gcc -o linkedListTest.exe linkedListTest.o linkedList.o -Wall

linkedListTest.o: linkedListTest.c
		gcc -c linkedListTest.c -Wall

linkedList.o: linkedList.c
		gcc -c linkedList.c -Wall

clean: 
		rm -f *.o
		rm -f linkedListTest.exe