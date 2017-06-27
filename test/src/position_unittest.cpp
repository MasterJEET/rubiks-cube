/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "gtest/gtest.h"
#include "position.h"
#include "testcommon.h"

class PositionTest : public ::testing::Test {
    protected:
        Position pf;
        Position pbl;
        Position pdrf;

        PositionTest(): pf(front), pbl(back, left), pdrf(down, right, front){}


};

TEST_F(PositionTest, constructors) {

    //Initialization with single FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Center, vecSide = { Front }", pf);

    //Initialization with double FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Edge, vecSide = { Back Left }", pbl);

    //Initialization with triple FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Down Right Front }", pdrf); 
}

TEST_F(PositionTest, minions) {
    //getPositionType()
    EXPECT_EQ(corner, pdrf.getPositionType());
    //getSideAt(), index within range
    EXPECT_EQ(left, pbl.getSideAt(1));
    //getSideAt(), index out of range
    EXPECT_EQ(undefside, pbl.getSideAt(2));
    //getVecSide()
    const std::vector<FaceSide> *pvecSide = pf.getSide();
    EXPECT_EQ(front, pvecSide->at(0));
}

TEST_F(PositionTest, equality) {
    EXPECT_TRUE(Position(front) == Position(front));
    EXPECT_TRUE(Position(front) == Position(front, F_UNDEFINED));
    EXPECT_TRUE(Position(front) == Position(front, F_UNDEFINED, F_UNDEFINED));
    EXPECT_FALSE(Position(front) == Position(right));
    EXPECT_TRUE(Position(front, left) == Position(front, left));
    EXPECT_TRUE(Position(front, left) == Position(front, left, F_UNDEFINED));
    EXPECT_TRUE(Position(front, left) == Position(front, F_UNDEFINED, left));
    EXPECT_FALSE(Position(front, left) == Position(front, down));
    EXPECT_FALSE(Position(front, left) == Position(left, front));
    EXPECT_TRUE(Position(front, left, down) == Position(front, left, down));
    EXPECT_TRUE(Position(front, left, down) == Position(front, down, left));
    EXPECT_FALSE(Position(front, left, down) == Position(front, left, up));
    EXPECT_FALSE(Position(front, left, down) == Position(left, front, down));
}

TEST_F(PositionTest, inequality) {
    EXPECT_TRUE( Position(back, right, down) != Position(front, right, down) );
    EXPECT_FALSE( Position(back, right, down) != Position(back, down, right) );
}
