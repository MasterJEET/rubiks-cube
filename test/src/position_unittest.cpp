/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "gtest/gtest.h"
#include "position.h"

class PositionTest : public ::testing::Test {
    protected:
        Position pf;
        Position pbl;
        Position pdrf;

        PositionTest(): pf(front), pbl(back, left), pdrf(down, right, front){}
};

TEST_F(PositionTest, constructors) {
    std::stringstream ss;
    std::string pos;

    ss << pf;
    std::getline(ss, pos);
    EXPECT_EQ("Position: ptype = Center, vecSide = { Front }", pos);
    ss.str("");
    ss.clear();
}
