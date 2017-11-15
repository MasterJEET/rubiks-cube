/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 18th Jun 2017
 *
 * */

#include "gtest/gtest.h"
#include "testcommon.h"
#include "facelet.h"

class FaceletTest : public ::testing::Test {
    protected:
        Facelet frl;
        Facelet flr;
        Facelet ffw;
        
        FaceletTest(): frl(red, left), flr(left, red), ffw(front, white) {
            ffw*=up;
        }
};

TEST_F(FaceletTest, Initialization) {
    // === Facelet(Color, FaceSide) ===
    // check Color
    EXPECT_EQ(red, frl.getColor());
    // check FaceSide
    EXPECT_EQ(left, frl.side());

    // === Facelet(FaceSide, Color) ===
    // check Color
    EXPECT_EQ(red, flr.getColor());
    // check FaceSide
    EXPECT_EQ(left, flr.side());
}

TEST_F(FaceletTest, setPosition) {
    // === Facelet(Color, FaceSide) ===
    frl.setPosition(right);
    EXPECT_EQ(right, frl.side());
    
    // === Facelet(FaceSide, Color) ===
    flr.setPosition(down);
    EXPECT_EQ(down, flr.side());
}

TEST_F(FaceletTest, overloading) {
    //Order is important in these tests

    //Simple multiplication
    EXPECT_EQ( Facelet(red, back), frl*up );
    //Multiplying Facelet with FaceSide which Facelet.side == FaceSide
    EXPECT_EQ( flr*left, Facelet(left, red) );
    //Compund assignment through multiplication, done is constructor
    EXPECT_EQ( Facelet(left, white) , ffw );
    //Chaining operator*
    EXPECT_EQ( Facelet(right, red), frl*front*front );
    //Chaining operator*=
    EXPECT_EQ( Facelet(down, red), (frl *= up) *= right );
}


TEST_F(FaceletTest, FaceletPosition){
    //Create few FaceletPositions
    FaceletPosition fp_fu( front, up );
    FaceletPosition fp_uf( up, front );
    FaceletPosition fp_bdl( back, down, left );
    FaceletPosition fp_bld( back, left, down );
    FaceletPosition fp_lbd( std::vector<FaceSide>{left, back, down} );

    EXPECT_FALSE( fp_fu == fp_uf );
    EXPECT_FALSE( fp_bdl != fp_bld );
    EXPECT_TRUE( fp_lbd != fp_bld );

}


TEST(Nonmember, opposition){
    Facelet f_fr(front, red);
    Facelet f_bg(back, green);
    Facelet f_ub(up, blue);
    Facelet f_rw(right, white);

    EXPECT_TRUE( areOpposite(f_fr, f_bg));
    EXPECT_FALSE( areOpposite(f_fr, f_ub));
    EXPECT_TRUE( anyOpposite(f_fr, f_ub, f_bg));
    EXPECT_FALSE( anyOpposite( f_ub, f_fr, f_rw ));
}
