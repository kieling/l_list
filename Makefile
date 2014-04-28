//CC = gcc -std=c99
//CFLAGS = -Wall
//LDFLAGS = -g


linkedListTest: linkedList.o linkedListTest.o
		gcc -o linkedListTest linkedListTest.o linkedList.o -Wall

linkedListTest.o: linkedListTest.c
		gcc -c linkedListTest.c -Wall -std=c99

linkedList.o: linkedList.c
		gcc -c linkedList.c -Wall -std=c99

clean: 
		rm -f *.o
		rm -f linkedListTest.exe