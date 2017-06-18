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

        Cubelet cr;
        Cubelet cfu;
        Cubelet cbld;

        CubeletTest(): frr(red, right), fwf(white, front), fbu(blue, up), fgb(green, back), fol(orange, left), fwd(white, down),
                       cr(frr), cfu(fwf, fbu), cbld(fgb, fol, fwd)
                       {}
};

TEST_F(CubeletTest, constructors) {
    std::stringstream ss;
    std::string clet;

    ss << cr;
    std::getline(ss, clet);
    EXPECT_EQ("Colors: { Red } Position: ptype = Center, vecSide = { Right }", clet);
    ss.str("");
    ss.clear();
    
    ss << cfu;
    std::getline(ss, clet);
    EXPECT_EQ("Colors: { White Blue } Position: ptype = Edge, vecSide = { Front Up }", clet);
    ss.str("");
    ss.clear();
    
    ss << cbld;
    std::getline(ss, clet);
    EXPECT_EQ("Colors: { Green Orange White } Position: ptype = Corner, vecSide = { Back Left Down }", clet);
}
