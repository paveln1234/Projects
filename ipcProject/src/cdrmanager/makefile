#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = ../../inc/
CFLAGS = -Wall
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/cdrmanager

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/cdrmanager

OBJ_DEBUG = $(OBJDIR_DEBUG)/fileHandler.o $(OBJDIR_DEBUG)/cdrMessager.o $(OBJDIR_DEBUG)/cdrParser.o $(OBJDIR_DEBUG)/cdrParserManager-test.o $(OBJDIR_DEBUG)/cdrParserManager.o $(OBJDIR_DEBUG)/discoverer.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/__/fileHandler.o $(OBJDIR_RELEASE)/cdrMessager.o $(OBJDIR_RELEASE)/cdrParser.o $(OBJDIR_RELEASE)/cdrParserManager-test.o $(OBJDIR_RELEASE)/cdrParserManager.o $(OBJDIR_RELEASE)/discoverer.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG)/__ || mkdir -p $(OBJDIR_DEBUG)/__
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/fileHandler.o: ../fileHandler.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ../fileHandler.c -o $(OBJDIR_DEBUG)/fileHandler.o

$(OBJDIR_DEBUG)/cdrMessager.o: cdrMessager.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c cdrMessager.c -o $(OBJDIR_DEBUG)/cdrMessager.o

$(OBJDIR_DEBUG)/cdrParser.o: cdrParser.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c cdrParser.c -o $(OBJDIR_DEBUG)/cdrParser.o

$(OBJDIR_DEBUG)/cdrParserManager-test.o: cdrParserManager-test.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c cdrParserManager-test.c -o $(OBJDIR_DEBUG)/cdrParserManager-test.o

$(OBJDIR_DEBUG)/cdrParserManager.o: cdrParserManager.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c cdrParserManager.c -o $(OBJDIR_DEBUG)/cdrParserManager.o

$(OBJDIR_DEBUG)/discoverer.o: discoverer.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c discoverer.c -o $(OBJDIR_DEBUG)/discoverer.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)/__
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE)/__ || mkdir -p $(OBJDIR_RELEASE)/__
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/__/fileHandler.o: ../fileHandler.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ../fileHandler.c -o $(OBJDIR_RELEASE)/__/fileHandler.o

$(OBJDIR_RELEASE)/cdrMessager.o: cdrMessager.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c cdrMessager.c -o $(OBJDIR_RELEASE)/cdrMessager.o

$(OBJDIR_RELEASE)/cdrParser.o: cdrParser.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c cdrParser.c -o $(OBJDIR_RELEASE)/cdrParser.o

$(OBJDIR_RELEASE)/cdrParserManager-test.o: cdrParserManager-test.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c cdrParserManager-test.c -o $(OBJDIR_RELEASE)/cdrParserManager-test.o

$(OBJDIR_RELEASE)/cdrParserManager.o: cdrParserManager.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c cdrParserManager.c -o $(OBJDIR_RELEASE)/cdrParserManager.o

$(OBJDIR_RELEASE)/discoverer.o: discoverer.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c discoverer.c -o $(OBJDIR_RELEASE)/discoverer.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)/__
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

