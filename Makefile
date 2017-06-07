# @author: MasterJEET
# @email : masterjeet9@gmail.com

CXX := g++
C11 := -std=c++11
CXXFLAGS := -g -rdynamic $(C11)
SRC := src
OBJ := obj
BIN := bin
INCLUDES := -I./inc

OBJECTS := $(OBJ)/common.o $(OBJ)/Position.o $(OBJ)/Facelet.o $(OBJ)/Cubelet.o $(OBJ)/main.o

TARGET := $(BIN)/cube

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

clean:
	rm obj/* bin/*

.PHONY: all clean
