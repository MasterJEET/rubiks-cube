/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 1Xth June 2017
 *
 * */

#include "gtest/gtest.h"
#include "position.h"
#include "testcommon.h"

class PositionTest : public ::testing::Test {
    protected:
        std::vector<FaceSide> vFS;
        Position pf;
        Position pbl;
        Position pdrf;
        Position plub_v;

        PositionTest(): vFS{left, up, back}, pf(front), pbl(back, left), pdrf(down, right, front), plub_v(vFS){

        }


};

TEST_F(PositionTest, constructors) {

    ///Initialization with single FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Center, vecSide = { Front }", pf);

    ///Initialization with double FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Edge, vecSide = { Back Left }", pbl);

    ///Initialization with triple FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Down Right Front }", pdrf); 

    ///Initialization with std::vector<FaceSide>
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Left Up Back }", plub_v); 
}

TEST_F(PositionTest, minions) {
    ///getPositionType()
    EXPECT_EQ(corner, pdrf.getPositionType());
    ///getSideAt(), index within range
    EXPECT_EQ(left, pbl.getSideAt(1));
    ///getSideAt(), index out of range
    EXPECT_EQ(undefside, pbl.getSideAt(2));
    ///getVecSide()
    const std::vector<FaceSide> *pvecSide = pf.getSide();
    EXPECT_EQ(front, pvecSide->at(0));
}

TEST_F(PositionTest, equality) {
    EXPECT_EQ(Position(front), Position(front));
    EXPECT_EQ(Position(front), Position(front, F_UNDEFINED));
    EXPECT_EQ(Position(front), Position(front, F_UNDEFINED, F_UNDEFINED));
    EXPECT_NE(Position(front), Position(right));
    EXPECT_EQ(Position(front, left), Position(front, left));
    EXPECT_EQ(Position(front, left), Position(front, left, F_UNDEFINED));
    EXPECT_EQ(Position(front, left), Position(front, F_UNDEFINED, left));
    EXPECT_NE(Position(front, left), Position(front, down));
    EXPECT_NE(Position(front, left), Position(left, front));
    EXPECT_EQ(Position(front, left, down), Position(front, left, down));
    EXPECT_NE(Position(front, left, down), Position(front, down, left));
    EXPECT_NE(Position(front, left, down), Position(front, left, up));
    EXPECT_NE(Position(front, left, down), Position(left, front, down));
}

TEST_F(PositionTest, inequality) {
    EXPECT_NE( Position(back, right, down), Position(front, right, down) );
    EXPECT_NE( Position(back, right, down), Position(back, down, right) );
}


TEST_F(PositionTest, size) {
    EXPECT_EQ(1, pf.size());
    EXPECT_EQ(2, pbl.size());
    EXPECT_EQ(3, pdrf.size());
    EXPECT_EQ(3, plub_v.size());

}


TEST_F(PositionTest, multiplication) {
    //////single//////
    ///different side
    pf *= left;
    ASSERT_EQ( pf, Position(down) );
    ///same side
    pf *= down;
    ASSERT_EQ( pf, Position(down) );
    ///opposite side
    pf *= up;
    ASSERT_EQ( pf, Position(down) );
    
    //////double//////
    ///same side on first
    pbl *= back;
    ASSERT_EQ(pbl, Position(back, down));
    ///same side on second
    pbl *= down;
    ASSERT_EQ(pbl, Position(left, down));
    ///opposite on first
    pbl *= right;
    ASSERT_EQ(pbl, Position(left, front));
    ///opposite on second
    pbl *= back;
    ASSERT_EQ(pbl, Position(down, front));
    ///different
    pbl *= right;
    ASSERT_EQ(pbl, Position(front, up));

    //////triple//////
    ///same side on first
    pdrf *= down;
    ASSERT_EQ(pdrf, Position(down, back, right) );
    ///same side on second
    pdrf *= back;
    ASSERT_EQ(pdrf, Position(right, back, up) );
    ///same side on third
    pdrf *= up;
    ASSERT_EQ(pdrf, Position(front, right, up) );
    ///opposite on first
    pdrf *= back;
    ASSERT_EQ(pdrf, Position(front, up, left) );
    ///opposite on second
    pdrf *= down;
    ASSERT_EQ(pdrf, Position(right, up, front) );
    ///opposite on third
    pdrf *= back;
    ASSERT_EQ(pdrf, Position(up, left, front) );
    ///different
    ///not possible
    
    ///few corner cases
    Position p1(front);
    EXPECT_THROW(p1*=undefside, std::runtime_error);

    Position p3 = pdrf*right;
    ASSERT_EQ( p3, Position(back, left, up) );
}
