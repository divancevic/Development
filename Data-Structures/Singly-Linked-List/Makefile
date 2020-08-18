TARGET:test
test:./SinglyLinkedList.o ./test.o
	gcc test.o SinglyLinkedList.o -o test

SinglyLinkedList.o:./SinglyLinkedList.c
	gcc -c -I ./ ./SinglyLinkedList.c -o SinglyLinkedList.o

test.o:./test.c
	gcc -c ./test.c -o test.o
clean:
	rm ./*.o
	rm test
