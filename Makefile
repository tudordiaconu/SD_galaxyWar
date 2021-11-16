
build:
	gcc -Wall -Wextra -std=c99 galactic_war.c CircularDoublyLinkedList.c GameCommands.c -o main

run:
	./main

clean:
	rm -f main