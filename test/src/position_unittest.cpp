/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 1Xth June 2017
 *
 * */

#include "gtest/gtest.h"
#include "cube.h"
#include "testcommon.h"

typedef CollectionWrapper<FaceSide,false> Position;

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

    //Initialization with single FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Center, vecSide = { Front }", pf);

    //double FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Edge, vecSide = { Back Left }", pbl);

    //triple FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Down Right Front }", pdrf); 

    //std::vector<FaceSide>
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Left Up Back }", plub_v); 
}

TEST_F(PositionTest, minions) {
    EXPECT_EQ(corner, pdrf.ptype());
    EXPECT_EQ(left, pbl.second());
    EXPECT_EQ(undefside, pbl.third());
    const std::vector<FaceSide> pvecSide = pf.all();
    EXPECT_EQ(front, pvecSide.at(0));
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
    EXPECT_EQ(Position(front, left), Position(left, front));
    EXPECT_EQ(Position(front, left, down), Position(front, left, down));
    EXPECT_EQ(Position(front, left, down), Position(front, down, left));
    EXPECT_NE(Position(front, left, down), Position(front, left, up));
    EXPECT_EQ(Position(front, left, down), Position(left, front, down));
}

TEST_F(PositionTest, inequality) {
    EXPECT_NE( Position(back, right, down), Position(front, right, down) );
    EXPECT_EQ( Position(back, right, down), Position(back, down, right) );
}


TEST_F(PositionTest, num) {
    EXPECT_EQ(1, pf.num());
    EXPECT_EQ(2, pbl.num());
    EXPECT_EQ(3, pdrf.num());
    EXPECT_EQ(3, plub_v.num());

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
    
    /////few corner cases
    //Position p1(front);
    //EXPECT_THROW(p1*=undefside, std::runtime_error);

    //Position p3 = pdrf*right;
    //std::cout << "p3: " << p3 << std::endl;
    //std::cout << "pdrf: " << pdrf << std::endl;
    //ASSERT_EQ( p3, Position(back, left, up) );
}


TEST_F(PositionTest, relative){
    Position P(front, left, down);
    EXPECT_EQ(P.relative(right), Position(left,back,down));
    EXPECT_EQ(P.relative(left), Position(right,front,down));
    EXPECT_EQ(P.relative(up), Position(down,left,back));
    EXPECT_EQ(P.relative(down), Position(up,left,front));
    EXPECT_EQ(P.relative(front), Position(front,left,down));
    EXPECT_EQ(P.relative(back), Position(back,right,down));


    Position P2(back, undefside, up);
    EXPECT_EQ(P2.relative(up), Position(up,front));
    EXPECT_EQ(P2.relative(right), Position(right,up,undefside));
    EXPECT_EQ(P2.relative(back), Position(front,undefside,up));


}

TEST_F(PositionTest, result)
{
    Step s(down,2);
    Position pGet = pdrf.result(s);

    EXPECT_EQ(pGet, Position(down, left, back));

    StepSequence seq({s});
    seq.push_back({right,false,1,true});
    Position pGet2 = pdrf.result(seq);

    EXPECT_EQ(pGet2, pGet);
}


TEST(Step, constructor)
{
    Step s1(back, 1, true);

    EXPECT_EQ(s1.f, back);
    EXPECT_EQ(s1.is_clockwise, true);
    EXPECT_EQ(s1.no_of_turns, 1);


    Step s2(right,false, 2);

    EXPECT_EQ(s2.f, right);
    EXPECT_EQ(s2.is_clockwise, false);
    EXPECT_EQ(s2.no_of_turns, 2);


    Step s3(up, true);

    EXPECT_EQ(s3.f, up);
    EXPECT_EQ(s3.is_clockwise, true);
    EXPECT_EQ(s3.no_of_turns, 1);


    Step s4(down, 3);

    EXPECT_EQ(s4.f, down);
    EXPECT_EQ(s4.is_clockwise, true);
    EXPECT_EQ(s4.no_of_turns, 3);


    Step s5(left);

    EXPECT_EQ(s5.f, left);
    EXPECT_EQ(s5.is_clockwise, true);
    EXPECT_EQ(s5.no_of_turns, 1);


    Step s6;

    EXPECT_EQ(s6.f, undefside);
    //EXPECT_EQ(s6.is_clockwise, true);
    //EXPECT_EQ(s6.no_of_turns, 1);
}



TEST(Position, isOn)
{
    Position p1(front,undefside,up);

    EXPECT_TRUE(p1.isOn(front));
    EXPECT_TRUE(p1.isOn(up));
    EXPECT_FALSE(p1.isOn(back));
}



TEST(Position, affectable)
{
    Position P_corner(front,up,right);

    Step F(front);
    EXPECT_TRUE(P_corner.affectable(F));

    Step u(up,false);
    EXPECT_TRUE(P_corner.affectable(u));

    Step R(right);
    EXPECT_TRUE(P_corner.affectable(R));

    Step b(back,false);
    EXPECT_FALSE(P_corner.affectable(b));

    Step D(down);
    EXPECT_FALSE(P_corner.affectable(D));

    Step l(left,false);
    EXPECT_FALSE(P_corner.affectable(l));

    Step bm(front,false,1,true);
    EXPECT_FALSE(P_corner.affectable(bm));

    Position P_edge(back,left);

    EXPECT_TRUE(P_edge.affectable(b));
    Step Um(up,true,1,true);
    EXPECT_TRUE(P_edge.affectable(Um));
    EXPECT_FALSE(P_edge.affectable(u));
    Step f(front,false);
    EXPECT_FALSE(P_edge.affectable(f));

}


TEST(CollectionWrapper, stdsizet)
{
#define WRAPPERSIZE_TEST(T,b,x,n,...)\
    CollectionWrapper<T,b> x(__VA_ARGS__);\
    EXPECT_EQ(x,n);

    //CubeletType, single FaceSide
    WRAPPERSIZE_TEST(FaceSide,false,cwfn0,0,front);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn1,1,back);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn2,2,up);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn3,3,down);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn4,4,left);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn5,5,right);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn1_1,1,back,undefside);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn4_1,4,left,undefside,undefside);

    //CubeletType, double FaceSide
    WRAPPERSIZE_TEST(FaceSide,false,cwfn6,6,front,up);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn7,7,front,down);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn7_1,7,down,front);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn8,8,front,left);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn9,9,front,right);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn10,10,back,up);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn11,11,back,down);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn11_1,11,down,back);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn12,12,back,left);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn13,13,back,right);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn14,14,up,left);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn15,15,up,right);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn15_1,15,right,up);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn16,16,down,left);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn17,17,down,right);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn17_1,17,right,down);

    //CubeletType, triple FaceSide
    WRAPPERSIZE_TEST(FaceSide,false,cwfn18,18,front,up,left);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn19,19,front,up,right);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn19_1,19,front,right,up);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn20,20,front,down,left);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn21,21,front,down,right);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn22,22,back,up,left);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn23,23,back,up,right);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn23_1,23,up,right,back);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn24,24,back,down,left);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn25,25,back,down,right);
    WRAPPERSIZE_TEST(FaceSide,false,cwfn25_1,25,right,back,down);


    //FaceletType, single FaceSide
    WRAPPERSIZE_TEST(FaceSide,true,cwff0,0,front);
    WRAPPERSIZE_TEST(FaceSide,true,cwff1,1,back);
    WRAPPERSIZE_TEST(FaceSide,true,cwff2,2,up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff3,3,down);
    WRAPPERSIZE_TEST(FaceSide,true,cwff4,4,left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff5,5,right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff0_1,0,front,undefside);
    WRAPPERSIZE_TEST(FaceSide,true,cwff3_1,3,down,undefside,undefside);

    //FaceletType, double FaceSide
    WRAPPERSIZE_TEST(FaceSide,true,cwff6, 6, front, up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff7, 7, front, down);
    WRAPPERSIZE_TEST(FaceSide,true,cwff8, 8, front, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff9, 9, front, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff10, 10, back, up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff11, 11, back, down);
    WRAPPERSIZE_TEST(FaceSide,true,cwff11_1, 11, back, down, undefside);
    WRAPPERSIZE_TEST(FaceSide,true,cwff12, 12, back, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff13, 13, back, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff14, 14, up, front);
    WRAPPERSIZE_TEST(FaceSide,true,cwff15, 15, up, back);
    WRAPPERSIZE_TEST(FaceSide,true,cwff16, 16, up, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff17, 17, up, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff18, 18, down, front);
    WRAPPERSIZE_TEST(FaceSide,true,cwff19, 19, down, back);
    WRAPPERSIZE_TEST(FaceSide,true,cwff20, 20, down, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff21, 21, down, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff21_1, 21, down, right, undefside);
    WRAPPERSIZE_TEST(FaceSide,true,cwff22, 22, left, front);
    WRAPPERSIZE_TEST(FaceSide,true,cwff23, 23, left, back);
    WRAPPERSIZE_TEST(FaceSide,true,cwff24, 24, left, up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff25, 25, left, down);
    WRAPPERSIZE_TEST(FaceSide,true,cwff26, 26, right, front);
    WRAPPERSIZE_TEST(FaceSide,true,cwff27, 27, right, back);
    WRAPPERSIZE_TEST(FaceSide,true,cwff28, 28, right, up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff29, 29, right, down);
    WRAPPERSIZE_TEST(FaceSide,true,cwff29_1, 29, right, undefside, down);

    //FaceletType, Triple FaceSide
    WRAPPERSIZE_TEST(FaceSide,true,cwff30, 30, front, up, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff30_1, 30, front, left, up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff31, 31, front, up, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff31_1, 31, front, right, up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff32, 32, front, down, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff32_1, 32, front, left, down);
    WRAPPERSIZE_TEST(FaceSide,true,cwff33, 33, front, down, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff33_1, 33, front, right, down);
    WRAPPERSIZE_TEST(FaceSide,true,cwff34, 34, back, up, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff35, 35, back, up, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff36, 36, back, down, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff37, 37, back, down, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff38, 38, up, front, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff39, 39, up, front, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff40, 40, up, back, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff41, 41, up, back, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff42, 42, down, front, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff42_1, 42, down, left, front);
    WRAPPERSIZE_TEST(FaceSide,true,cwff43, 43, down, front, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff44, 44, down, back, left);
    WRAPPERSIZE_TEST(FaceSide,true,cwff44_1, 44, down, left, back);
    WRAPPERSIZE_TEST(FaceSide,true,cwff45, 45, down, back, right);
    WRAPPERSIZE_TEST(FaceSide,true,cwff46, 46, left, front, up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff47, 47, left, front, down);
    WRAPPERSIZE_TEST(FaceSide,true,cwff48, 48, left, back, up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff49, 49, left, back, down);
    WRAPPERSIZE_TEST(FaceSide,true,cwff50, 50, right, front, up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff51, 51, right, front, down);
    WRAPPERSIZE_TEST(FaceSide,true,cwff52, 52, right, back, up);
    WRAPPERSIZE_TEST(FaceSide,true,cwff53, 53, right, back, down);

#undef  WRAPPERSIZE_TEST

}


TEST(CollectionWrapper, equality)
{

#define CC_EQUALITY(b,lcc,rcc,lf,...) \
    CollectionWrapper<FaceSide,b> lcc(lf);\
    CollectionWrapper<FaceSide,b> rcc(__VA_ARGS__);\
    EXPECT_EQ(lcc, rcc);

    CC_EQUALITY(false,lcc1,rcc1,front,front);
    CC_EQUALITY(true,lcc2,rcc2,front,front);
    //CC_EQUALITY(true,lcc3,rcc3,undefside,undefside);

#undef  CC_EQUALITY

#define CCD_EQUALITY(b,op,lcc,rcc,lf1,lf2,...) \
    CollectionWrapper<FaceSide,b> lcc(lf1,lf2);\
    CollectionWrapper<FaceSide,b> rcc(__VA_ARGS__);\
    EXPECT_TRUE(lcc op rcc);

    CCD_EQUALITY(false,==,ldcc1,rdcc1,front,up,up,front);
    CCD_EQUALITY(true,!=,ldcc2,rdcc2,front,up,up,front);
    CCD_EQUALITY(false,==,ldcc3,rdcc3,right,down,down,right,undefside);
    CCD_EQUALITY(false,==,ldcc4,rdcc4,back,left,left,undefside,back);
    CCD_EQUALITY(true,!=,ldcc4_1,rdcc4_1,back,left,left,undefside,back);
    //CCD_EQUALITY(false,!=,ldcc5,rdcc5,front,down,undefside,down,front);

#undef  CCD_EQUALITY

#define CCT_EQUALITY(b,op,lcc,rcc,lf1,lf2,lf3,...) \
    CollectionWrapper<FaceSide,b> lcc(lf1,lf2,lf3);\
    CollectionWrapper<FaceSide,b> rcc(__VA_ARGS__);\
    EXPECT_TRUE(lcc op rcc);

    CCT_EQUALITY(false,==,ltcc1,rtcc1,down,left,back,back,left,down);
    CCT_EQUALITY(true,!=,ltcc2,rtcc2,down,left,back,back,left,down);

#undef  CCT_EQUALITY

}


TEST(CollectionWrapper, vector_constructor)
{
    typedef CollectionWrapper<FaceSide,true> FletPos;
    std::vector<FaceSide> v0;
    EXPECT_NO_THROW( FletPos cw0(v0) );

    std::vector<FaceSide> v1({left});
    CollectionWrapper<FaceSide,false> cw1(v1);
    EXPECT_EQ( cw1.first(), left );
    EXPECT_EQ( cw1.second(), undefside );
    EXPECT_EQ( cw1.third(), undefside );

    std::vector<FaceSide> v2({undefside, back});
    CollectionWrapper<FaceSide,false> cw2(v2);
    EXPECT_EQ( cw2.first(), undefside );
    EXPECT_EQ( cw2.second(), back );
    EXPECT_EQ( cw2.third(), undefside );

    std::vector<FaceSide> v3({right, down});
    CollectionWrapper<FaceSide,false> cw3(v3);
    EXPECT_EQ( cw3.first(), right);
    EXPECT_EQ( cw3.second(), down );
    EXPECT_EQ( cw3.third(), undefside );

    std::vector<FaceSide> v4({left, down, front});
    CollectionWrapper<FaceSide,false> cw4(v4);
    EXPECT_EQ( cw4.first(), left);
    EXPECT_EQ( cw4.second(), down );
    EXPECT_EQ( cw4.third(), front );

    std::vector<FaceSide> v5({right, undefside, up});
    CollectionWrapper<FaceSide,false> cw5(v5);
    EXPECT_EQ( cw5.first(), right);
    EXPECT_EQ( cw5.second(), undefside );
    EXPECT_EQ( cw5.third(), up );

    //more than three input
    std::vector<FaceSide> v6({front,left,down,undefside});
    EXPECT_THROW( FletPos cw6(v6), std::runtime_error );

    //contain opposite faces
    std::vector<FaceSide> v7({front,up,back});
    EXPECT_THROW( FletPos cw6(v7), std::runtime_error );
}

TEST(CollectionWrapper, isOn)
{
    CollectionWrapper<FaceSide,false> p1(front,undefside,up);

    EXPECT_TRUE(p1.isOn(front));
    EXPECT_TRUE(p1.isOn(up));
    EXPECT_FALSE(p1.isOn(back));
}

TEST(CollectionWrapper, relative){

    CollectionWrapper<FaceSide,true> P(front, left, down);
    CollectionWrapper<FaceSide,true> cw1(left,back,down);
    EXPECT_EQ(P.relative(right), cw1);
    CollectionWrapper<FaceSide,true> cw2(right,front,down);
    EXPECT_EQ(P.relative(left), cw2);
    CollectionWrapper<FaceSide,true> cw3(down,left,back);
    EXPECT_EQ(P.relative(up), cw3);
    CollectionWrapper<FaceSide,true> cw4(up,left,front);
    EXPECT_EQ(P.relative(down), cw4);
    CollectionWrapper<FaceSide,true> cw5(front,left,down);
    EXPECT_EQ(P.relative(front), cw5);
    CollectionWrapper<FaceSide,true> cw6(back,right,down);
    EXPECT_EQ(P.relative(back), cw6);

    CollectionWrapper<FaceSide,true> P2(back, undefside, up);
    CollectionWrapper<FaceSide,true> cw7(up,front);
    EXPECT_EQ(P2.relative(up), cw7);
    CollectionWrapper<FaceSide,true> cw8(right,up,undefside);
    EXPECT_EQ(P2.relative(right), cw8);
    CollectionWrapper<FaceSide,true> cw9(front,undefside,up);
    EXPECT_EQ(P2.relative(back), cw9);

}


TEST(CollectionWrapper, affectable)
{
    CollectionWrapper<FaceSide,true> P_corner(front,up,right);

    Step F(front);
    EXPECT_TRUE(P_corner.affectable(F));

    Step u(up,false);
    EXPECT_TRUE(P_corner.affectable(u));

    Step R(right);
    EXPECT_TRUE(P_corner.affectable(R));

    Step b(back,false);
    EXPECT_FALSE(P_corner.affectable(b));

    Step D(down);
    EXPECT_FALSE(P_corner.affectable(D));

    Step l(left,false);
    EXPECT_FALSE(P_corner.affectable(l));

    Step bm(front,false,1,true);
    EXPECT_FALSE(P_corner.affectable(bm));

    CollectionWrapper<FaceSide,true> P_edge(back,left);

    EXPECT_TRUE(P_edge.affectable(b));
    Step Um(up,true,1,true);
    EXPECT_TRUE(P_edge.affectable(Um));
    EXPECT_FALSE(P_edge.affectable(u));
    Step f(front,false);
    EXPECT_FALSE(P_edge.affectable(f));

}


TEST(CollectionWrapper, result)
{
    CollectionWrapper<FaceSide,false> pdrf(down,right,front);
    Step s(down,2);
    CollectionWrapper<FaceSide,false> pGet = pdrf.result(s);

    CollectionWrapper<FaceSide,false> cw1(down, left, back);
    EXPECT_EQ(pGet, cw1);

    StepSequence seq({s});
    seq.push_back({right,false,1,true});
    CollectionWrapper<FaceSide,false> pGet2 = pdrf.result(seq);

    EXPECT_EQ(pGet2, pGet);
}


TEST(CollectionWrapper, display) {

    typedef CollectionWrapper<FaceSide,false> Pos;

    //Initialization with single FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Center, vecSide = { Front }", Pos(front));

    //Initialization with double FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Edge, vecSide = { Back Left }", Pos(back,left));

    //Initialization with triple FaceSide
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Down Right Front }", Pos(down,right,front)); 

    //Initialization with std::vector<FaceSide>
    std::vector<FaceSide> v({left,up,back});
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Left Up Back }", Pos(v));
}
