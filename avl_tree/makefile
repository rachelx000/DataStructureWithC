avl: AVLTree.c test_avl.c
	gcc -o avl AVLTree.c test_avl.c

run: avl
	./avl

check_leaks: avl
	leaks --atExit -- ./avl

clean:
	rm -f ./avl