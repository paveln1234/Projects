CC = gcc
HPATH = ../../inc/
SPATH =	 ./src/
LIBDS = ../../../../advc/inc/
LIBSMAKE = ../../../../advc/
EXE_NAME = uiclient
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
OBJC = uiclient.o


#exec
uiclient.o: 
	$(CC) -o uiclient $(FLAGS) uiclient.c -I ../../inc/
 
# To obtain object files
%.o: %.c $(HFILE)
	$(CC) -c $(CFLAGS) $< -o $@
 	
##cdrMessager
#cdrMessager.o: cdrMessager.c
#	$(CC) -g -c -o  cdrMessager.o $(FLAGS)  cdrMessager.c

##cdrParser
#cdrParser.o: cdrParser.c 
#	$(CC) -g -c -o  cdrParser.o $(FLAGS)  	cdrParser.c


##discoverer
#discoverer.o: discoverer.c 
#	$(CC) -g -c -o  discoverer.o $(FLAGS)  	discoverer.c

##cdrParserManager
#cdrParserManager.o: cdrParserManager.c 
#	$(CC) -g -c -o  cdrParserManager.o $(FLAGS) cdrParserManager.c


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
	./uiclient
