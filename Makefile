all: cube

CPP = g++
CPPFLAGS += -g -Wall -Wextra -rdynamic -std=c++11 -I.

cube.o: cube.h cube.cpp
	$(CPP) $(CPPFLAGS) -c cube.cpp

cube: cube.o main.cpp
	$(CPP) $(CPPFLAGS) cube.o main.cpp -o cube

clean:
	rm -rf cube cube.o

test: cube
	./cube < ./test/linear.dat

.PHONY: test clean
