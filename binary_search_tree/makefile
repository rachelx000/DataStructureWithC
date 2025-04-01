bst: BinarySearchTree.c test_bst.c ../queue/Queue.c ../dynamic_array/DynamicArray.c
	gcc -o bst BinarySearchTree.c test_bst.c ../queue/Queue.c ../dynamic_array/DynamicArray.c

run: bst
	./bst

check_leaks: bst
	leaks --atExit -- ./bst

clean:
	rm -f ./bst