bst: BinarySearchTree.c test_bst.c
	gcc -o bst BinarySearchTree.c test_bst.c

run: bst
	./bst

check_leaks: bst
	leaks --atExit -- ./bst

clean:
	rm -f ./bst