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
TEST_OBJ += common_unittest.o position_unittest.o facelet_unittest.o cubelet_unittest.o cube_unittest.o algobase_unittest.o


# All objects for original program ( excluding those of test cases and 'main')
ALL_OBJ += common.o position.o facelet.o cubelet.o cube.o algobase.o
# All source files for cube
CUBE_SRC += $(SRC_DIR)/*.cpp $(INC_DIR)/*.h


# House-keeping build targets.

all : rubiktest

clean :
	rm -f *.o *.a *.out common* facelet* position* cube* rubik* algobase*

cleanall :
	make clean
	cd $(GTEST_MAKE); make clean

cube-all.o : $(CUBE_SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/cube-all.cpp

main.o : $(CUBE_SRC) main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c main.cpp


# Libraries, this project
librubiks-cube.a : cube-all.o
	$(AR) $(ARFLAGS) $@ $^

librubiks-cube_main.a : cube-all.o main.o
	$(AR) $(ARFLAGS) $@ $^


# Libraries, googletest
$(GTEST_MAKE)/gtest.a :
	cd $(GTEST_MAKE); make gtest.a

$(GTEST_MAKE)/gtest_main.a :
	cd $(GTEST_MAKE); make gtest_main.a


%_unittest.o : $(TEST_DIR)/src/%_unittest.cpp $(INC_DIR)/%.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< 

%_ : %_unittest.o librubiks-cube_main.a $(GTEST_MAKE)/gtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

rubiktest :  $(TEST_OBJ) librubiks-cube_main.a  $(GTEST_MAKE)/gtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
