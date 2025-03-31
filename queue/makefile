queue: Queue.c test_queue.c ../dynamic_array/DynamicArray.c
	gcc -o queue Queue.c test_queue.c ../dynamic_array/DynamicArray.c

run: queue
	./queue

check_leaks: queue
	leaks --atExit -- ./queue

clean:
	rm -f ./queue