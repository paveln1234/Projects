HPATH = ..mak/inc/
CC = gcc
FLAGS = -Wall -ansi -pedantic -I $(HPATH)

VEC_PATH = ../vector/
LIST_PATH =../list/
QUEUE_PATH = ../queue/
HEAP_PATH = ../heap/
STACK_PATH = ../stack/
HASH_PATH = ../hashmap/
TREE_PATH = ../tree/


#objects
OBJC = vector.o queue.o safeThreadQueue.o heap.o stack.o safeThreadHashMap.o hashmap.o list.o list_itr.o list_functions.o 

#Data Structures static lib
libds.a: $(OBJC)
	ar rcs libds.a $(OBJC)

#vector	
vector.o: $(VEC_PATH)vector.c 
	$(CC) -g -c -o  vector.o $(FLAGS)  $(VEC_PATH)vector.c
	
#heap 
heap.o: $(HEAP_PATH)heap.c 
	$(CC) -g -c -o  heap.o $(FLAGS) $(HEAP_PATH)heap.c

#tree 
tree.o: $(TREE_PATH)tree.c 
	$(CC) -g -c -o  tree.o $(FLAGS)  $(TREE_PATH)tree.c

#queue
queue.o: $(QUEUE_PATH)queue.c 
	$(CC) -g -c -o  queue.o $(FLAGS) $(QUEUE_PATH)queue.c

#safeThreadQueue
safeThreadQueue.o: $(QUEUE_PATH)safeThreadQueue.c
	$(CC) $(COMP) -g -c -o safeThreadQueue.o $(FLAGS) $(QUEUE_PATH)safeThreadQueue.c

#stack
stack.o: $(STACK_PATH)stack.c 
	$(CC) -g -c -o  stack.o $(FLAGS)  $(STACK_PATH)stack.c

#hash
hashmap.o: $(HASH_PATH)hashmap.c
	$(CC) -g -c -o  hashmap.o $(FLAGS)  $(HASH_PATH)hashmap.c -lm

#safeThreadHashMap
safeThreadHashMap.o: $(HASH_PATH)safeThreadHashMap.c
	$(CC) $(COMP) -g -c -o safeThreadHashMap.o $(FLAGS) $(HASH_PATH)safeThreadHashMap.c -lm

#list
list.o: $(LIST_PATH)list.c 
	$(CC) -g -c -o  list.o $(FLAGS)  $(LIST_PATH)list.c

#list_itr
list_itr.o: $(LIST_PATH)list_itr.c 
	$(CC) -g -c -o  list_itr.o $(FLAGS)  $(LIST_PATH)list_itr.c

#list_function
list_functions.o: $(LIST_PATH)list_functions.c 
	$(CC) -g -c -o  list_functions.o $(FLAGS)  $(LIST_PATH)list_functions.c


#clean
clean: 
	rm -f $(OBJC) libds.a 
	rm -f libds





