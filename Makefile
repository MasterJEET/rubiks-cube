BIN_DIR := bin
OBJ_DIR := obj
LIB_DIR := lib
INC_DIR := inc
SRC_DIR := src
TEST_DIR := test

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(TEST_DIR) -I $(INC_DIR)

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -rdynamic -std=c++11

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TEST_OBJ += $(OBJ_DIR)/common_unittest.o
TEST_OBJ += $(OBJ_DIR)/facelet_unittest.o
TEST_OBJ += $(OBJ_DIR)/position_unittest.o
TEST_OBJ += $(OBJ_DIR)/cubelet_unittest.o
TEST_OBJ += $(OBJ_DIR)/cube_unittest.o

# House-keeping build targets.

all : $(BIN_DIR)/cubetest

clean :
	rm -rf $(BIN_DIR) $(OBJ_DIR)
	rm -f $(LIB_DIR)/librubiks*

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LIB_DIR)/librubiks-cube.a : $(OBJ_DIR)/common.o $(OBJ_DIR)/position.o $(OBJ_DIR)/facelet.o $(OBJ_DIR)/cubelet.o $(OBJ_DIR)/cube.o
	@mkdir -p $(OBJ_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%_unittest.o : $(TEST_DIR)/src/%_unittest.cpp $(INC_DIR)/%.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/% :  $(OBJ_DIR)/%_unittest.o $(LIB_DIR)/librubiks-cube.a  $(LIB_DIR)/gtest_main.a
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

$(BIN_DIR)/cubetest :  $(TEST_OBJ) $(LIB_DIR)/librubiks-cube.a  $(LIB_DIR)/gtest_main.a
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
