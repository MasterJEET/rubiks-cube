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

TEST(FaceletPosition, TypeOperator){

    EXPECT_THROW(int x = FaceletPosition(), std::runtime_error);

    EXPECT_EQ(0, FaceletPosition(front));
    
    EXPECT_EQ(1, FaceletPosition(front,up));
    EXPECT_EQ(2, FaceletPosition(front,right));
    EXPECT_EQ(3, FaceletPosition(front,down));
    EXPECT_EQ(4, FaceletPosition(front,left));

    EXPECT_EQ(5, FaceletPosition(front,up,right));
    EXPECT_EQ(5, FaceletPosition(front,right,up));
    EXPECT_EQ(6, FaceletPosition(front,right,down));
    EXPECT_EQ(6, FaceletPosition(front,down,right));
    EXPECT_EQ(7, FaceletPosition(front,down,left));
    EXPECT_EQ(7, FaceletPosition(front,left,down));
    EXPECT_EQ(8, FaceletPosition(front,left,up));
    EXPECT_EQ(8, FaceletPosition(front,up,left));


    EXPECT_EQ(9, FaceletPosition(back));
    
    EXPECT_EQ(10, FaceletPosition(back,up));
    EXPECT_EQ(11, FaceletPosition(back,left));
    EXPECT_EQ(12, FaceletPosition(back,down));
    EXPECT_EQ(13, FaceletPosition(back,right));

    EXPECT_EQ(14, FaceletPosition(back,up,left));
    EXPECT_EQ(14, FaceletPosition(back,left,up));
    EXPECT_EQ(15, FaceletPosition(back,left,down));
    EXPECT_EQ(15, FaceletPosition(back,down,left));
    EXPECT_EQ(16, FaceletPosition(back,down,right));
    EXPECT_EQ(16, FaceletPosition(back,right,down));
    EXPECT_EQ(17, FaceletPosition(back,right,up));
    EXPECT_EQ(17, FaceletPosition(back,up,right));


    EXPECT_EQ(18, FaceletPosition(up));
    
    EXPECT_EQ(19, FaceletPosition(up,back));
    EXPECT_EQ(20, FaceletPosition(up,right));
    EXPECT_EQ(21, FaceletPosition(up,front));
    EXPECT_EQ(22, FaceletPosition(up,left));

    EXPECT_EQ(23, FaceletPosition(up,right,back));
    EXPECT_EQ(23, FaceletPosition(up,back,right));
    EXPECT_EQ(24, FaceletPosition(up,front,right));
    EXPECT_EQ(24, FaceletPosition(up,right,front));
    EXPECT_EQ(25, FaceletPosition(up,left,front));
    EXPECT_EQ(25, FaceletPosition(up,front,left));
    EXPECT_EQ(26, FaceletPosition(up,back,left));
    EXPECT_EQ(26, FaceletPosition(up,left,back));


    EXPECT_EQ(27, FaceletPosition(down));
    
    EXPECT_EQ(28, FaceletPosition(down,front));
    EXPECT_EQ(29, FaceletPosition(down,right));
    EXPECT_EQ(30, FaceletPosition(down,back));
    EXPECT_EQ(31, FaceletPosition(down,left));

    EXPECT_EQ(32, FaceletPosition(down,right,front));
    EXPECT_EQ(32, FaceletPosition(down,front,right));
    EXPECT_EQ(33, FaceletPosition(down,back,right));
    EXPECT_EQ(33, FaceletPosition(down,right,back));
    EXPECT_EQ(34, FaceletPosition(down,left,back));
    EXPECT_EQ(34, FaceletPosition(down,back,left));
    EXPECT_EQ(35, FaceletPosition(down,front,left));
    EXPECT_EQ(35, FaceletPosition(down,left,front));


    EXPECT_EQ(36, FaceletPosition(left));
    
    EXPECT_EQ(37, FaceletPosition(left,up));
    EXPECT_EQ(38, FaceletPosition(left,front));
    EXPECT_EQ(39, FaceletPosition(left,down));
    EXPECT_EQ(40, FaceletPosition(left,back));

    EXPECT_EQ(41, FaceletPosition(left,up,front));
    EXPECT_EQ(41, FaceletPosition(left,front,up));
    EXPECT_EQ(42, FaceletPosition(left,front,down));
    EXPECT_EQ(42, FaceletPosition(left,down,front));
    EXPECT_EQ(43, FaceletPosition(left,down,back));
    EXPECT_EQ(43, FaceletPosition(left,back,down));
    EXPECT_EQ(44, FaceletPosition(left,back,up));
    EXPECT_EQ(44, FaceletPosition(left,up,back));


    EXPECT_EQ(45, FaceletPosition(right));
    
    EXPECT_EQ(46, FaceletPosition(right,up));
    EXPECT_EQ(47, FaceletPosition(right,back));
    EXPECT_EQ(48, FaceletPosition(right,down));
    EXPECT_EQ(49, FaceletPosition(right,front));

    EXPECT_EQ(50, FaceletPosition(right,up,back));
    EXPECT_EQ(50, FaceletPosition(right,back,up));
    EXPECT_EQ(51, FaceletPosition(right,back,down));
    EXPECT_EQ(51, FaceletPosition(right,down,back));
    EXPECT_EQ(52, FaceletPosition(right,down,front));
    EXPECT_EQ(52, FaceletPosition(right,front,down));
    EXPECT_EQ(53, FaceletPosition(right,front,up));
    EXPECT_EQ(53, FaceletPosition(right,up,front));

}
