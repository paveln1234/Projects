CC = gcc
HPATH = ./inc/
SPATH = ./src/
LIBDS = ../../advc/inc/
LIBSMAKE = ../../advc/


FLAGS = -Wall -ansi -pedantic -I $(HPATH) -I $(LIBDS)


#phony

#objects
OBJC = barrier.o 
LIBS = libds.a

#exec
barrier: $(OBJC) $(LIBSMAKE)$(LIBS)
	$(CC) -o barrier $(FLAGS) $(OBJC) $(LIBSMAKE)$(LIBS) -pthread $(SPATH)barrier-test.c
 	
#barrier
barrier.o: $(SPATH)barrier.c $(HPATH)barrier.h
	$(CC) -g -c -o  barrier.o $(FLAGS)  $(SPATH)barrier.c


#libslibs
$(LIBSMAKE)$(LIBS): $(LIBS)

#make libds.a -C mean the der path
$(LIBS) : 
	$(MAKE) $(LIBS) -C $(LIBSMAKE) 

#clean 
clean: 
	rm -f *.o 


#run test unit
run:
	barrier
