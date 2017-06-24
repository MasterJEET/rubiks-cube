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
            std::string filepath = std::string() + std::getenv("CUBE_HOME") + "/test/dat/front.dat";
            ifs.open( filepath  );
            if(!ifs)
                throw std::runtime_error("Couldn't open file: \"" + filepath + "\"");
            else
                cube = Cube(ifs);
        }
};

TEST_F(CubeTest, constructor) {
    std::stringstream ss;
    Facelet f1 = cube.getFacelet(front, undefside, undefside);

    ss << f1;
    EXPECT_EQ("Facelet: col = White, side = Front", ss.str());
}

