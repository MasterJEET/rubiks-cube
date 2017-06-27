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
        Facelet fwf;
        Facelet fbu;
        Facelet fgb;
        Facelet fol;
        Facelet fwd;
        
        Position pfrd;
        
        Cubelet cr;
        Cubelet cfu;
        Cubelet cbld;

        CubeletTest(): frr(red, right), fwf(white, front), fbu(blue, up), fgb(green, back), fol(orange, left), fwd(white, down),
                       pfrd(front, right, down),
                       cr(&frr), cfu(&fwf, &fbu), cbld(&fgb, &fol, &fwd)
                       {}
};

TEST_F(CubeletTest, constructors) {

    EXPECT_PRED_FORMAT2(checkPrint, "Colors: { Red } Position: ptype = Center, vecSide = { Right }", cr);
    EXPECT_PRED_FORMAT2(checkPrint, "Colors: { White Blue } Position: ptype = Edge, vecSide = { Front Up }", cfu);
    EXPECT_PRED_FORMAT2(checkPrint, "Colors: { Green Orange White } Position: ptype = Corner, vecSide = { Back Left Down }", cbld);
    
}

TEST_F(CubeletTest, vecside) {
    const std::vector<Facelet*> *pvecSide = cbld.getFacelet();

    EXPECT_PRED_FORMAT2(checkPrint, "Back", pvecSide->at(0)->getFaceSide());
    EXPECT_PRED_FORMAT2(checkPrint, "Green", pvecSide->at(0)->getColor());
    
    EXPECT_PRED_FORMAT2(checkPrint, "Left", pvecSide->at(1)->getFaceSide());
    EXPECT_PRED_FORMAT2(checkPrint, "Orange", pvecSide->at(1)->getColor());

    EXPECT_PRED_FORMAT2(checkPrint, "Down", pvecSide->at(2)->getFaceSide());
    EXPECT_PRED_FORMAT2(checkPrint, "White", pvecSide->at(2)->getColor());

}

TEST_F(CubeletTest, get) {

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Front", cfu.getFaceletAt(0));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Up", cfu.getFaceletAt(1));
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Center, vecSide = { Right }", cr.getPosition());
    
}

TEST_F(CubeletTest, set) {

    cbld.setPosition(pfrd);
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Front Right Down }", cbld.getPosition());

}


TEST_F(CubeletTest, overloading) {
    EXPECT_TRUE(Cubelet(&frr) == Cubelet(&frr));
    EXPECT_TRUE(Cubelet(&frr) != Cubelet(&fwf));
}
