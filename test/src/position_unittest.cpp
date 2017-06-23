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

    //Initialization with single FaceSide
    ss << pf;
    std::getline(ss, pos);
    EXPECT_EQ("Position: ptype = Center, vecSide = { Front }", pos);
    ss.str("");
    ss.clear();

    //Initialization with double FaceSide
    ss << pbl;
    std::getline(ss, pos);
    EXPECT_EQ("Position: ptype = Edge, vecSide = { Back Left }", pos);
    ss.str("");
    ss.clear();

    //Initialization with triple FaceSide
    ss << pdrf;
    std::getline(ss, pos);
    EXPECT_EQ("Position: ptype = Corner, vecSide = { Down Right Front }", pos);
}

TEST_F(PositionTest, minions) {
    //getPositionType()
    EXPECT_EQ(corner, pdrf.getPositionType());
    //getSideAt()
    EXPECT_EQ(left, pbl.getSideAt(1));
    //getVecSide()
    const std::vector<FaceSide> *pvecSide = pf.getSide();
    EXPECT_EQ(front, pvecSide->at(0));
}
