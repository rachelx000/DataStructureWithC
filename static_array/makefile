starray: StaticArrayBasics.c
	gcc -o starray StaticArrayBasics.c

run: starray
	./starray

check_leaks: starray
	leaks --atExit -- ./starray

clean:
	rm -f ./starray