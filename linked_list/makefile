linked_list: LinkedList.c test_linkedlist.c
	gcc -o linked_list LinkedList.c test_linkedlist.c

run: linked_list
	./linked_list

check_leaks: linked_list
	leaks --atExit -- ./linked_list

clean:
	rm -f ./linked_list