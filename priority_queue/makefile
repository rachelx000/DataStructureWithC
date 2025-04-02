pq: PriorityQueue.c test_pq.c ../dynamic_array/DynamicArray.c
	gcc -o pq PriorityQueue.c test_pq.c ../dynamic_array/DynamicArray.c

run: pq
	./pq

check_leaks: pq
	leaks --atExit -- ./pq

clean:
	rm -f ./pq