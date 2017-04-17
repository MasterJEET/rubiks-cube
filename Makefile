# @author: MasterJEET
# @email : masterjeet9@gmail.com

CXX := g++
C11 := -std=c++11
CXXFLAGS := -g $(C11)
SRC := src
OBJ := obj
BIN := bin
INCLUDES := -I./inc
OBJECTS := $(OBJ)/main.o $(OBJ)/Position.o $(OBJ)/Facelet.o $(OBJ)/common.o $(OBJ)/Cubelet.o
TARGET := $(BIN)/cube

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(C11) $^ -o $@

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r obj bin

makedir:
	mkdir bin obj

.PHONY: all clean makedir 
