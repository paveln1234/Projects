CC = gcc
HPATH = ../../inc/
SPATH =	 ./src/
LIBDS = ../../../../advc/inc/
LIBSMAKE = ../../../../advc/
EXE_NAME = ui-test

#$(bits)
CFLAGS = -g -pedantic -ansi  -Wall -I $(HPATH) -I $(LIBDS)
CC = gcc

.Phony : clean rebuild run

# find out if its a 64bit machine
LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
	# do 64 bit stuff here, like set some CFLAGS
	bits = -m32
else
	# do 32 bit stuff here
	bits =
endif


#phony

#objects
OBJC = uiserver.o ui-test.o
LIBS = libds.a

#exec
ui-test:$(OBJC) $(LIBSMAKE)$(LIBS)
	$(CC) -o ui-test $(FLAGS) $(OBJC) $(LIBSMAKE)$(LIBS)   -pthread


# To obtain object files
%.o: %.c $(HFILE)
	$(CC) -c $(CFLAGS) $< -o $@

#libslibs
$(LIBSMAKE)$(LIBS): $(LIBS)

#make libds.a -C mean the der path
$(LIBS) :
	$(MAKE) $(LIBS) -C $(LIBSMAKE)

#clean
clean:
	rm -f *.o
	rm -f *~
	rm -f $(EXE_NAME)


#run test unit
run:
	./$(EXE_NAME)
