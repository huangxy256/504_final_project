ALL: test_lorenz

DEBUG ?= FALSE

CXXFLAGS := -Wall -Wextra -Wpedantic -Wshadow -g

ifeq (${DEBUG}, TRUE)
   CXXFLAGS += -g
else
   CXXFLAGS += -DNDEBUG -O3
endif

test_lorenz.o: lorenz.H
	g++ -std=c++17 -c test_lorenz.cpp

test_lorenz: test_lorenz.o
	g++ -std=c++17 -o test_lorenz test_lorenz.o

clean:
	rm -f *.o test_lorenz


ALL: test_lorenz


