dynarray: DynamicArray.c test_dynarray.c
	gcc -o dynarray DynamicArray.c test_dynarray.c

run: dynarray
	./dynarray

check_leaks: dynarray
	leaks --atExit -- ./dynarray

clean:
	rm -f ./dynarray