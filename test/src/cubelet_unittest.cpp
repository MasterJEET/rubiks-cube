/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 17th Apr 2017
 *
 * */

#include "gtest/gtest.h"
#include "cubelet.h"
#include "testcommon.h"


class CubeletTest : public ::testing::Test {
    protected:
        Facelet frr;
        FaceletPosition fp_fu;
        Facelet fwf;
        FaceletPosition fp_uf;
        Facelet fbu;

        FaceletPosition fp_bld;
        FaceletPosition fp_ldb;
        FaceletPosition fp_dbl;
        Facelet fgb;
        Facelet fol;
        Facelet fwd;
        
        CubeletPosition pfrd;
        
        Cubelet cr;
        Cubelet cfu;
        Cubelet cbld;

        CubeletTest(): frr(red, right), fp_fu(front, up), fwf(white, fp_fu), fp_uf(up, front), fbu(blue, fp_uf),
                       fp_bld(back, left, down), fp_ldb(left, down, back), fp_dbl(down, back, left), fgb(green, fp_bld), fol(orange, fp_ldb), fwd(white, fp_dbl),
                       pfrd(front, right, down),
                       cr(frr), cfu(fwf, fbu), cbld(fgb, fol, fwd)
                       {}
};

TEST_F(CubeletTest, constructors) {

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Right, R) }", cr);
    
}

TEST_F(CubeletTest, vecside) {

    EXPECT_EQ(Back, cbld.getFacelet(fp_bld).side());
    EXPECT_EQ(Green, cbld.getFacelet(fp_bld).getColor());
    
    EXPECT_EQ(Left, cbld.getFacelet(fp_ldb).side());
    EXPECT_EQ(Orange, cbld.getFacelet(fp_ldb).getColor());

    EXPECT_EQ(Down, cbld.getFacelet(fp_dbl).side());
    EXPECT_EQ(White, cbld.getFacelet(fp_dbl).getColor());

}

TEST_F(CubeletTest, get) {

    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Center, vecSide = { Right }", cr.getPosition());

    listFletPos lFP;
    lFP.push_back(fp_bld);
    lFP.push_back(fp_ldb);
    lFP.push_back(fp_dbl);

    EXPECT_EQ( lFP, cbld.getEquivalentFletPosList() );

    vecFacelet vF;
    vF.push_back(fwf);
    vF.push_back(fbu);

    EXPECT_EQ( vF, cfu.getFacelet() );
}

TEST_F(CubeletTest, set) {

    cbld.setPosition(pfrd);
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Front Right Down }", cbld.getPosition());

}


TEST_F(CubeletTest, overloading) {
    EXPECT_TRUE(Cubelet(frr) == Cubelet(frr));
    EXPECT_TRUE(Cubelet(frr) != Cubelet(fwf));
}


TEST_F(CubeletTest, ColorSetEquality)
{
    Cubelet cr_new(cr);
    Cubelet cfu_new(cfu);
    Cubelet cbld_new(cbld);

    cr_new *= right;
    EXPECT_TRUE(haveSameColors(cr, cr_new));

    cfu_new *= down;
    EXPECT_TRUE(haveSameColors(cfu, cfu_new));

    cbld_new *= back;
    EXPECT_TRUE(haveSameColors(cbld, cbld_new));
}


TEST_F(CubeletTest, CubeletPosition){
    //Create CubeletPositons
    CubeletPosition cp_f(front);
    CubeletPosition cp_fl(front, left);
    CubeletPosition cp_fld(front, left, down);
    CubeletPosition cp_fdl(front, down, left);
    CubeletPosition cp_dfl( down,front, left);
    CubeletPosition cp_fur(front,up,right);
    CubeletPosition cp_bdl(back,down,left);
    CubeletPosition cp_fnl(left,undefside, front);

    EXPECT_FALSE( cp_f == cp_fl );
    EXPECT_FALSE( cp_fld != cp_fdl );
    EXPECT_FALSE( cp_dfl != cp_fdl );

    EXPECT_EQ( getCommonFace(cp_fur, cp_fdl), front );
    EXPECT_EQ( getCommonFace(cp_fur, cp_bdl), undefside );
    EXPECT_EQ( getCommonFace(cp_fnl, cp_fl), left );

}


TEST_F(CubeletTest, vectorinitializer){
    //Create vector of Facelets
    std::vector<Facelet> vf{fgb, fol, fwd};
    Cubelet c1(vf);
    EXPECT_EQ(c1.getFacelet(fp_bld), Facelet(green, fp_bld));
    EXPECT_EQ(c1.getFacelet(fp_ldb), Facelet(orange, fp_ldb));
    EXPECT_EQ(c1.getFacelet(fp_dbl), Facelet(white, fp_dbl));
    EXPECT_THROW( Cubelet(frr, fwf, fgb) , std::runtime_error );
}

TEST_F(CubeletTest, multiplication){
    
    //Center Cubelet rotation
    ASSERT_EQ(Cubelet({front, red}), cr *= up);
    EXPECT_EQ(Cubelet({left, red}), cr *= up );
    ASSERT_EQ(Cubelet({back, red}), cr *= up);
    ASSERT_EQ(CubeletPosition(back), cr.getPosition());

    //Edge Cubelet rotation
    ASSERT_EQ(Cubelet(Facelet( {back,up}, blue), Facelet( {up,back}, white)), cfu*=right);
    ASSERT_EQ(Cubelet(Facelet( {left,up}, blue), Facelet( {up,left}, white)), cfu*=down);
    ASSERT_EQ(Cubelet(Facelet( {down,left}, blue), Facelet( {left,down}, white)), cfu*=back);
    ASSERT_EQ(CubeletPosition(down, left), cfu.getPosition());

    //Corner Cubelet rotation
    ASSERT_EQ(Cubelet( Facelet( {back,up,left}, green), Facelet( {up,left,back}, orange), Facelet( {left,back,up}, white ) ), cbld*=front);
    ASSERT_EQ(Cubelet( Facelet( {up,front,left}, green), Facelet( {front,left,up}, orange), Facelet( {left,up,front}, white ) ), cbld*=left);
    ASSERT_EQ(Cubelet( Facelet( {right,front,up}, green), Facelet( {front,up,right}, orange), Facelet( {up,right,front}, white ) ), cbld*=front);
    ASSERT_EQ(CubeletPosition(front, up, right), cbld.getPosition());
}


TEST(Cubelet, TypeOperator){

    EXPECT_EQ(0, CubeletPosition(front));
    EXPECT_EQ(1, CubeletPosition(back));
    EXPECT_EQ(2, CubeletPosition(up));
    EXPECT_EQ(3, CubeletPosition(down));
    EXPECT_EQ(4, CubeletPosition(left));
    EXPECT_EQ(5, CubeletPosition(right));

    EXPECT_EQ(6, CubeletPosition(front,up));
    EXPECT_EQ(6, CubeletPosition(up,front));
    EXPECT_EQ(7, CubeletPosition(front,down));
    EXPECT_EQ(8, CubeletPosition(front,left));
    EXPECT_EQ(9, CubeletPosition(front,right));
    EXPECT_EQ(10, CubeletPosition(back,up));
    EXPECT_EQ(11, CubeletPosition(back,down));
    EXPECT_EQ(11, CubeletPosition(down,back));
    EXPECT_EQ(12, CubeletPosition(back,left));
    EXPECT_EQ(13, CubeletPosition(back,right));
    EXPECT_EQ(14, CubeletPosition(up,left));
    EXPECT_EQ(15, CubeletPosition(up,right));
    EXPECT_EQ(15, CubeletPosition(right,up));
    EXPECT_EQ(16, CubeletPosition(down,left));
    EXPECT_EQ(17, CubeletPosition(down,right));

    EXPECT_EQ(18, CubeletPosition(front,up,left));
    EXPECT_EQ(18, CubeletPosition(up,left,front));
    EXPECT_EQ(18, CubeletPosition(left,front,up));
    EXPECT_EQ(18, CubeletPosition(front,left,up));
    EXPECT_EQ(18, CubeletPosition(up,front,left));
    EXPECT_EQ(18, CubeletPosition(left,up,front));
    EXPECT_EQ(19, CubeletPosition(front,up,right));
    EXPECT_EQ(20, CubeletPosition(front,down,left));
    EXPECT_EQ(21, CubeletPosition(front,down,right));
    EXPECT_EQ(22, CubeletPosition(back,up,left));
    EXPECT_EQ(23, CubeletPosition(back,up,right));
    EXPECT_EQ(24, CubeletPosition(back,down,left));
    EXPECT_EQ(25, CubeletPosition(back,down,right));

}


TEST(colorset, constructor){
    SetOfColor cs1(red, white, blue);
    EXPECT_TRUE(cs1.min() <= cs1.mid());
    EXPECT_TRUE(cs1.mid() <= cs1.max());

    SetOfColor cs2(yellow, green, orange);
    EXPECT_TRUE(cs2.min() <= cs2.mid());
    EXPECT_TRUE(cs2.mid() <= cs2.max());

    SetOfColor cs3(yellow, red);
    EXPECT_TRUE(cs3.min() <= cs3.mid());
    EXPECT_TRUE(cs3.mid() <= cs3.max());

    SetOfColor cs4(green);
    EXPECT_TRUE(cs4.min() <= cs4.mid());
    EXPECT_TRUE(cs4.mid() <= cs4.max());

    //same Color
    EXPECT_THROW( SetOfColor cs5(red, red), std::runtime_error );
    //Opposite Color
    EXPECT_THROW( SetOfColor cs5(white, green, white), std::runtime_error );

    std::vector<Color> vCol1;
    EXPECT_THROW( SetOfColor cs6(vCol1), std::runtime_error );    //Empty vector
    vCol1.push_back(yellow);
    vCol1.push_back(orange);
    vCol1.push_back(blue);

    SetOfColor cs7(vCol1);
    EXPECT_TRUE(cs7.min() <= cs7.mid());
    EXPECT_TRUE(cs7.mid() <= cs7.max());

    vCol1.push_back( green );
    EXPECT_THROW( SetOfColor cs8(vCol1), std::runtime_error );    //Size > 3


}


TEST(CubeletPosition, areClockwise)
{
    CubeletPosition cpFrom(front,down,left);
    CubeletPosition cpTo(front,down,right);

    EXPECT_TRUE(areClockwise(cpFrom,cpTo,down));
    EXPECT_FALSE(areClockwise(cpFrom,cpTo,front));

    EXPECT_THROW(areClockwise(cpFrom,cpTo,left), std::runtime_error);

    CubeletPosition cpFrom2(front,down);

    EXPECT_FALSE(areClockwise(cpFrom2, cpTo,down));
}
