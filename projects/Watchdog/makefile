
main : vector.o heap.o heapify.o priority_q_heap.o scheduler_heap.o uid.o task_heap.o wd_shared.o
	gcc -shared -Wl,-soname,libwd.so -o libwd.so ./*.o; \
	gcc -pedantic-errors -Wall -Wextra -g -pthread -c -fPIC wd_thread.c -I./include/ -I../../ds/include/; \
	gcc -pedantic-errors -Wall -Wextra -g -pthread -c -fPIC wd_api.c -I./include/ -I../../ds/include/; \
	gcc -pedantic-errors -Wall -Wextra -g -pthread -c -fPIC wd_app.c -I./include/ -I../../ds/include/; \
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC user_app.c -I./include/ -I../../ds/include/; \
	gcc wd_thread.o wd_api.o wd_app.o -Wl,-rpath,./ -L. -lwd -lpthread -o wd.out; \
	gcc wd_thread.o wd_api.o user_app.o -Wl,-rpath,./ -L. -lwd -lpthread -o user_app.out; \
		

vector.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC ../../ds/vector.c -I ../../ds/include/ 

heap.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC ../../ds/heap.c -I ../../ds/include/ 

heapify.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC ../../ds/heapify.c -I ../../ds/include/ 

priority_q_heap.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC ../../ds/priority_q_heap.c -I ../../ds/include/ 

scheduler_heap.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC ../../ds/scheduler_heap.c -I ../../ds/include/ 

uid.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC ../../ds/uid.c -I ../../ds/include/ 

task_heap.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC ../../ds/task_heap.c -I ../../ds/include/

wd_shared.o		:
	gcc -pedantic-errors -Wall -Wextra -g -pthread -c -fPIC wd_shared.c -I./include/ -I../../ds/include/
	




clean:
	rm *.o; \
	rm *.so
