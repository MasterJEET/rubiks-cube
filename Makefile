INC_DIR := ./inc
SRC_DIR := ./src
TEST_DIR := ./test

# Googletest directories
GTEST_DIR := ./googletest/googletest
GTEST_MAKE := $(GTEST_DIR)/make

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include -I$(INC_DIR) -I$(TEST_DIR)

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -rdynamic -std=c++11

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TEST_OBJ += common_unittest.o
TEST_OBJ += facelet_unittest.o
TEST_OBJ += position_unittest.o
TEST_OBJ += cubelet_unittest.o
TEST_OBJ += cube_unittest.o


# All objects for original program ( excluding those of test cases and 'main')
ALL_OBJ += common.o facelet.o position.o cubelet.o cube.o


## Dependencies and Source files
# common
COMMON_SRC += $(SRC_DIR)/common.cpp $(INC_DIR)/common.h  $(INC_DIR)/Color.def $(INC_DIR)/FaceSide.def $(INC_DIR)/PositionType.def
# facelet
FACELET_SRC += $(COMMON_SRC) $(SRC_DIR)/facelet.cpp $(INC_DIR)/facelet.h
# position
POSITION_SRC += $(FACELET_SRC) $(SRC_DIR)/position.cpp $(INC_DIR)/position.h
# cubelet
CUBELET_SRC += $(POSITION_SRC) $(SRC_DIR)/cubelet.cpp $(INC_DIR)/cubelet.h
# cube
CUBE_SRC += $(CUBELET_SRC) $(SRC_DIR)/cube.cpp $(INC_DIR)/cube.h


## Combination of libraries ensuring only one main program in project
# including googletest main
GTEST_MAIN += librubiks-cube.a  $(GTEST_MAKE)/gtest_main.a
# including main from rubiks-cube
RUBIK_MAIN += librubiks-cube_main.a  $(GTEST_MAKE)/gtest.a


# House-keeping build targets.

all : rubiktest

clean :
	rm -f *.o *.a *.out common* facelet* position* cube* rubik*

cleanall :
	make clean
	cd $(GTEST_MAKE); make clean

common.o : $(COMMON_SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/common.cpp 

facelet.o : $(FACELET_SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/facelet.cpp 

position.o : $(POSITION_SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/position.cpp 

cubelet.o : $(CUBELET_SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/cubelet.cpp 

cube.o : $(CUBE_SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/cube.cpp 

main.o : $(CUBE_SRC) main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c main.cpp 


# Libraries, this project
librubiks-cube.a : $(ALL_OBJ)
	$(AR) $(ARFLAGS) $@ $^

librubiks-cube_main.a : $(ALL_OBJ) main.o
	$(AR) $(ARFLAGS) $@ $^

# Libraris, googletest
$(GTEST_MAKE)/gtest.a :
	cd $(GTEST_MAKE); make gtest.a

$(GTEST_MAKE)/gtest_main.a :
	cd $(GTEST_MAKE); make gtest_main.a

%_unittest.o : $(TEST_DIR)/src/%_unittest.cpp $(INC_DIR)/%.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< 

%_ut :  %_unittest.o librubiks-cube_main.a  $(GTEST_MAKE)/gtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

rubiktest :  $(TEST_OBJ) librubiks-cube_main.a  $(GTEST_MAKE)/gtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
