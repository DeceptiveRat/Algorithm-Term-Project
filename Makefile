#-----------------------------------------------------------------------------#
## C++ compiler
#CC=g++
#
## Compiler flags
#CFLAGS=-c -Wall
#
## Linker flags
#LDFLAGS=
#
## Source files
#SOURCES=main.cpp
#
## Object files (generated from source files)
#OBJECTS=$(SOURCES:.cpp=.o)
#
## Executable file name
#EXECUTABLE=myprogram
#
## Default target - builds the executable
#all: $(EXECUTABLE)
#
## Target to build with debugging flags
#debug: CFLAGS += -DDEBUG -g
#debug: $(EXECUTABLE)
#
## Rule to build the executable
#$(EXECUTABLE): $(OBJECTS)
#	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
#
# Pattern rule to build object files from source files
#.cpp.o:
#	$(CC) $(CFLAGS) $< -o $@
#
## Clean target - removes generated files
#clean:
#	rm -f $(OBJECTS) $(EXECUTABLE)
#-----------------------------------------------------------------------------#

CC=g++

CFLAGS=-c -Wall

LDFLAGS=

SOURCES := $(wildcard *.cpp)

ALLSOURCES := $(wildcard *.cpp) $(wildcard *.h)

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=exe

all:$(EXECUTABLE)

debug:CFLAGS+= -DDEBUG -g
debug:$(EXECUTABLE)

debugNoOpt:CFLAGS+= -DDEBUG -g -O0
debugNoOpt:$(EXECUTABLE)

ASAN: CFLAGS+= -DDEBUG -g -fsanitize=address
ASAN: LDFLAGS+= -fsanitize=address
ASAN:$(EXECUTABLE)

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

oldText ?= foo
newText ?= bar
	
replace:
	@for file in $(ALLSOURCES); do \
		sed -i.bak 's/$(oldText)/$(newText)/g' $$file; \
	done
