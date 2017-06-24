/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 24th Jun 2017
 *
 * */

#include <fstream>
#include "cube.h"
#include "gtest/gtest.h"

class CubeTest: public ::testing::Test {
    protected:
        Cube cube;
        std::ifstream ifs;

        CubeTest() {
            std::string strCUBE_HOME = std::getenv("CUBE_HOME");
            ifs.open( strCUBE_HOME + "/dat/front.dat" );
            if(!ifs)
                throw std::runtime_error("Couldn't open file: \"" + strCUBE_HOME + "\"");
            else
                cube = Cube(ifs);
        }
};

TEST_F(CubeTest, constructor) {
    pairFaceSide pFS1(front, back);
    pairFaceSide pFS2(back, front);
    EXPECT_EQ(pFS1, pFS2);
    typedef std::pair<int, int> Pair;
    Pair p1(1,2);
    Pair p2(2,1);
    EXPECT_EQ(p1, p2);
}
