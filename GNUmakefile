ALL: test_lorenz

# get all the sources and the headers
SOURCE := $(wildcard *.cpp)
HEADERS := $(wildcard *.H)

# create the list of objects by replacing the .cpp with .o for the
# sources
OBJECTS := $(SOURCE:.cpp=.o)

# by default, debug mode will be disabled
DEBUG ?= FALSE

CXXFLAGS := -Wall -Wextra -Wpedantic -Wshadow -g

ifeq (${DEBUG}, TRUE)
   CXXFLAGS += -g
else
   CXXFLAGS += -DNDEBUG -O3
endif

# general rule for compiling a .cpp file to .o
%.o : %.cpp ${HEADERS}
	g++ -std=c++17 -c $<

# explicitly list the rule for creating the executable
test_lorenz: ${OBJECTS}
	g++ -std=c++17 -o $@ ${OBJECTS}

# 'make clean' will erase all the intermediate objects
clean:
	rm -f *.o test_lorenz