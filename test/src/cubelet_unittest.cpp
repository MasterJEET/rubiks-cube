/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 17th Apr 2017
 *
 * */

#include "gtest/gtest.h"
#include "cubelet.h"


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
                       cr(frr), cfu(fwf, fbu), cbld(fgb, fol, fwd)
                       {}
};

TEST_F(CubeletTest, constructors) {
    std::stringstream ss;

    ss << cr;
    EXPECT_EQ("Colors: { Red } Position: ptype = Center, vecSide = { Right }", ss.str());
    ss.str("");
    
    ss << cfu;
    EXPECT_EQ("Colors: { White Blue } Position: ptype = Edge, vecSide = { Front Up }", ss.str());
    ss.str("");
    
    ss << cbld;
    EXPECT_EQ("Colors: { Green Orange White } Position: ptype = Corner, vecSide = { Back Left Down }", ss.str());
}

TEST_F(CubeletTest, vecside) {
    std::stringstream ss;
    const std::vector<Facelet> *pvecSide = cbld.getFacelet();

    ss << pvecSide->at(0).getFaceSide();
    EXPECT_EQ("Back", ss.str());
    ss.str("");
    ss << pvecSide->at(0).getColor();
    EXPECT_EQ("Green", ss.str());
    ss.str("");
    
    ss << pvecSide->at(1).getFaceSide();
    EXPECT_EQ("Left", ss.str());
    ss.str("");
    ss << pvecSide->at(1).getColor();
    EXPECT_EQ("Orange", ss.str());
    ss.str("");

    ss << pvecSide->at(2).getFaceSide();
    EXPECT_EQ("Down", ss.str());
    ss.str("");
    ss << pvecSide->at(2).getColor();
    EXPECT_EQ("White", ss.str());

}

TEST_F(CubeletTest, get) {
    std::stringstream ss;

    ss << cfu.getFaceletAt(0);
    EXPECT_EQ("Facelet: col = White, side = Front", ss.str());
    ss.str("");
    
    ss << cfu.getFaceletAt(1);
    EXPECT_EQ("Facelet: col = Blue, side = Up", ss.str());
    ss.str("");

    ss << cr.getPosition();
    EXPECT_EQ("Position: ptype = Center, vecSide = { Right }", ss.str());
}

TEST_F(CubeletTest, set) {
    std::stringstream ss;

    cbld.setPosition(pfrd);
    ss << cbld.getPosition();
    EXPECT_EQ("Position: ptype = Corner, vecSide = { Front Right Down }", ss.str());
}
