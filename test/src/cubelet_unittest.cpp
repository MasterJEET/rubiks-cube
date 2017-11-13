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

    EXPECT_PRED_FORMAT2(checkPrint, "Back", cbld.getFacelet(fp_bld).side());
    EXPECT_PRED_FORMAT2(checkPrint, "G", cbld.getFacelet(fp_bld).getColor());
    
    EXPECT_PRED_FORMAT2(checkPrint, "Left", cbld.getFacelet(fp_ldb).side());
    EXPECT_PRED_FORMAT2(checkPrint, "O", cbld.getFacelet(fp_ldb).getColor());

    EXPECT_PRED_FORMAT2(checkPrint, "Down", cbld.getFacelet(fp_dbl).side());
    EXPECT_PRED_FORMAT2(checkPrint, "W", cbld.getFacelet(fp_dbl).getColor());

}

TEST_F(CubeletTest, get) {

    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Center, vecSide = { Right }", cr.getPosition());
    
}

TEST_F(CubeletTest, set) {

    cbld.setPosition(pfrd);
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Front Right Down }", cbld.getPosition());

}


TEST_F(CubeletTest, overloading) {
    EXPECT_TRUE(Cubelet(frr) == Cubelet(frr));
    EXPECT_TRUE(Cubelet(frr) != Cubelet(fwf));
}


TEST_F(CubeletTest, CubeletPosition){
    ///Create CubeletPositons
    CubeletPosition cp_f(front);
    CubeletPosition cp_fl(front, left);
    CubeletPosition cp_fld(front, left, down);
    CubeletPosition cp_fdl(front, down, left);
    CubeletPosition cp_dfl( down,front, left);

    EXPECT_FALSE( cp_f == cp_fl );
    EXPECT_FALSE( cp_fld != cp_fdl );
    EXPECT_FALSE( cp_dfl != cp_fdl );

}


TEST_F(CubeletTest, vectorinitializer){
    ///Create vector of Facelets
    std::vector<Facelet> vf{fgb, fol, fwd};
    Cubelet c1(vf);
    EXPECT_EQ(c1.getFacelet(fp_bld), Facelet(green, fp_bld));
    EXPECT_EQ(c1.getFacelet(fp_ldb), Facelet(orange, fp_ldb));
    EXPECT_EQ(c1.getFacelet(fp_dbl), Facelet(white, fp_dbl));
    EXPECT_THROW( Cubelet(frr, fwf, fgb) , std::runtime_error );
}
