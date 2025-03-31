stack: Stack.c test_stack.c ../linked_list/LinkedList.c
	gcc -o stack Stack.c test_stack.c ../linked_list/LinkedList.c

run: stack
	./stack

check_leaks: stack
	leaks --atExit -- ./stack

clean:
	rm -f ./stack