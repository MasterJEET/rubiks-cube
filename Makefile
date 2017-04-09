# @author: MasterJEET
# @email : masterjeet9@gmail.com

CXX := g++
CXXFLAGS := -g -std=c++11
SRC := src
OBJ := obj
BIN := bin
INCLUDES := -I ./include

# Linking command:
main : main.o
	$(CXX) $(OBJ)/main.o -o $(BIN)/main

Position : Position.o
	$(CXX) $(OBJ)/Position.o -o $(BIN)/Position

# Compiling command:
main.o : $(SRC)/main.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

Position.o : $(SRC)/Position.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $(SRC)/Position.cpp -o $(OBJ)/Position.o
