/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 17th Jun 2017
 *
 * */

///First google test ever
#include "gtest/gtest.h"
#include "common.h"
#include "testcommon.h"
#include <sstream>

class OverloadingTest : public ::testing::Test{
    protected:
        FaceSide f_front;
        FaceSide f_back;
        FaceSide f_up;
        FaceSide f_down;
        FaceSide f_right;
        FaceSide f_left;

        OverloadingTest(): f_front(front), f_back(back), f_up(up),
                           f_down(down), f_right(right), f_left(left)
        {
            f_front*=up;
            f_up*=right;
            f_right*=front;
        }

};

TEST(cubecell, faceside) {
    /* === For checking overloaded operator "<<" for FaceSide ===
     * Since these overloaded operators use FaceSide_str[] array
     * this testcase inherently validates it as well
     * === ===
     */

    EXPECT_PRED_FORMAT2(checkPrint, "Front", front);
    EXPECT_PRED_FORMAT2(checkPrint, "Back", back);
    EXPECT_PRED_FORMAT2(checkPrint, "Left", left);
    EXPECT_PRED_FORMAT2(checkPrint, "Right", right);
    EXPECT_PRED_FORMAT2(checkPrint, "Up", up);
    EXPECT_PRED_FORMAT2(checkPrint, "Down", down);
    EXPECT_PRED_FORMAT2(checkPrint, "F_UNDEFINED", undefside);
}

TEST(cubecell, color) {
    /* === For checking overloaded operator "<<" for Color ===
     * Since these overloaded operators use Color_str[] array
     * this testcase inherently validates it as well
     * === ===
     */


    EXPECT_PRED_FORMAT2(checkPrint, "R", red);
    EXPECT_PRED_FORMAT2(checkPrint, "W", white);
    EXPECT_PRED_FORMAT2(checkPrint, "Y", yellow);
    EXPECT_PRED_FORMAT2(checkPrint, "G", green);
    EXPECT_PRED_FORMAT2(checkPrint, "B", blue);
    EXPECT_PRED_FORMAT2(checkPrint, "O", orange);
    EXPECT_PRED_FORMAT2(checkPrint, "C_UNDEFINED", undefcol);

}


TEST(cubecell, positiontype) {
    /* === For checking overloaded operator "<<" for PositionType ===
     * Since these overloaded operators use PositionType_str[] array
     * this testcase inherently validates it as well
     * === ===
     */

    EXPECT_PRED_FORMAT2(checkPrint, "Center", center);
    EXPECT_PRED_FORMAT2(checkPrint, "Edge", edge);
    EXPECT_PRED_FORMAT2(checkPrint, "Corner", corner);
    EXPECT_PRED_FORMAT2(checkPrint, "P_UNDEFINED", undeftype);

}

TEST(cubemetabolism, opposite) {
    /* === Test function that check if presence of opposide FaceSides ==
     * =================================================================
     */
    EXPECT_TRUE(areOpposite(front,back));
    EXPECT_FALSE(areOpposite(up,right));
    EXPECT_TRUE(anyOpposite(down,left,right));
    EXPECT_FALSE(anyOpposite(up,right,back));
    
}

TEST(cubemetabolism, mapping) {
    /* === Test mapping of string to Color and  FaceSide ===
     * This test tests the following functions and glabal
     * map which are logically linked together to get FaceSide
     * or Color form single letter
     * 1. createmapColor()
     * 2. createmapFaceSide()
     * 3. toColor
     * 4. toFaceSide
     * 5. ColorFromLetter()
     * 6. FaceSideFromLetter()
     * Call to function 6. and 7. makes use of 1-4 hence
     * don't need to be tested explicitly
     * ==================================================
     */

    // Color from std::string with single letter
    Color col;
    ColorFromLetter(std::string("B"), col);
    EXPECT_EQ(blue, col);
    // Color from string literal of single character
    Color col1;
    ColorFromLetter("W", col1);
    EXPECT_EQ(white, col1);
    // Color from a single character literal
    Color col2;
    ColorFromLetter('G', col2);
    EXPECT_EQ(green, col2);
    // When letter does not represent any Color
    Color col3;
    EXPECT_FALSE(ColorFromLetter('X',col3));


    FaceSide fs;
    // FaceSide from std::string with single letter
    FaceSideFromLetter(std::string("D"), fs);
    EXPECT_EQ(down, fs);
    // FaceSide from string literal of single character
    FaceSide fs1;
    FaceSideFromLetter("L", fs1);
    EXPECT_EQ(left, fs1);
    // FaceSide from a single character literal
    FaceSide fs2;
    FaceSideFromLetter('B', fs2);
    EXPECT_EQ(back, fs2);
    // When letter doesn't represent any FaceSide
    FaceSide fs3;
    EXPECT_FALSE(FaceSideFromLetter('X',fs3));

}

TEST(faceside,equivalence){
    FaceSide f,u,r,d,l;

    f = front;
    setEquivalentFaceSide(f,u,r,d,l);
    EXPECT_EQ(up,u);
    EXPECT_EQ(right,r);
    EXPECT_EQ(down,d);
    EXPECT_EQ(left,l);

    f = back;
    setEquivalentFaceSide(f,u,r,d,l);
    EXPECT_EQ(up,u);
    EXPECT_EQ(left,r);
    EXPECT_EQ(down,d);
    EXPECT_EQ(right,l);

    f = up;
    setEquivalentFaceSide(f,u,r,d,l);
    EXPECT_EQ(back,u);
    EXPECT_EQ(right,r);
    EXPECT_EQ(front,d);
    EXPECT_EQ(left,l);

    f = down;
    setEquivalentFaceSide(f,u,r,d,l);
    EXPECT_EQ(front,u);
    EXPECT_EQ(right,r);
    EXPECT_EQ(back,d);
    EXPECT_EQ(left,l);

    f = left;
    setEquivalentFaceSide(f,u,r,d,l);
    EXPECT_EQ(up,u);
    EXPECT_EQ(front,r);
    EXPECT_EQ(down,d);
    EXPECT_EQ(back,l);

    f = right;
    setEquivalentFaceSide(f,u,r,d,l);
    EXPECT_EQ(up,u);
    EXPECT_EQ(back,r);
    EXPECT_EQ(down,d);
    EXPECT_EQ(front,l);
}


TEST(faceside, relative){

    FaceSide x = left;
    EXPECT_EQ(getRelativeFaceSide(x,front), left);
    EXPECT_EQ(getRelativeFaceSide(x,back), right);
    EXPECT_EQ(getRelativeFaceSide(x,up), left);
    EXPECT_EQ(getRelativeFaceSide(x,down), left);
    EXPECT_EQ(getRelativeFaceSide(x,right), back);
    EXPECT_EQ(getRelativeFaceSide(x,x), front);

    x = right;
    EXPECT_EQ(getRelativeFaceSide(x,front), right);
    EXPECT_EQ(getRelativeFaceSide(x,back), left);
    EXPECT_EQ(getRelativeFaceSide(x,up), right);
    EXPECT_EQ(getRelativeFaceSide(x,down), right);
    EXPECT_EQ(getRelativeFaceSide(x,left), back);
    EXPECT_EQ(getRelativeFaceSide(x,x), front);

    x = up;
    EXPECT_EQ(getRelativeFaceSide(x,front), up);
    EXPECT_EQ(getRelativeFaceSide(x,back), up);
    EXPECT_EQ(getRelativeFaceSide(x,left), up);
    EXPECT_EQ(getRelativeFaceSide(x,down), back);
    EXPECT_EQ(getRelativeFaceSide(x,right), up);
    EXPECT_EQ(getRelativeFaceSide(x,x), front);

    x = down;
    EXPECT_EQ(getRelativeFaceSide(x,front), down);
    EXPECT_EQ(getRelativeFaceSide(x,back), down);
    EXPECT_EQ(getRelativeFaceSide(x,up), back);
    EXPECT_EQ(getRelativeFaceSide(x,left), down);
    EXPECT_EQ(getRelativeFaceSide(x,right), down);
    EXPECT_EQ(getRelativeFaceSide(x,x), front);

    x = front;
    EXPECT_EQ(getRelativeFaceSide(x,left), right);
    EXPECT_EQ(getRelativeFaceSide(x,back), back);
    EXPECT_EQ(getRelativeFaceSide(x,up), down);
    EXPECT_EQ(getRelativeFaceSide(x,down), up);
    EXPECT_EQ(getRelativeFaceSide(x,right), left);
    EXPECT_EQ(getRelativeFaceSide(x,x), front);

    x = back;
    EXPECT_EQ(getRelativeFaceSide(x,front), back);
    EXPECT_EQ(getRelativeFaceSide(x,left), left);
    EXPECT_EQ(getRelativeFaceSide(x,up), up);
    EXPECT_EQ(getRelativeFaceSide(x,down), down);
    EXPECT_EQ(getRelativeFaceSide(x,right), right);
    EXPECT_EQ(getRelativeFaceSide(x,x), front);

}


TEST(input, next){
    std::string str = "\
                       #Following is an example of sample Face specification\n\
                       \
                       Front Red        #Here we spcify which side and color for center Facelet\n\
                       right Blue       # Color for edge Facelet at front\n\
                       Left orange      #Hey you reached last point\n";
    std::string letter;
    std::stringstream ss(str);

    next(ss,letter);
    EXPECT_EQ("F",letter);

    next(ss,letter);
    EXPECT_EQ("R",letter);

    next(ss,letter);
    EXPECT_EQ("R",letter);

    next(ss,letter);
    EXPECT_EQ("B",letter);

    next(ss,letter);
    EXPECT_EQ("L",letter);

    next(ss,letter);
    EXPECT_EQ("O",letter);

    EXPECT_FALSE(next(ss,letter));

}

TEST(input,assertColor){
    std::string str = "\
                       #Following is an example of sample Face specification\n\
                       \
                       Front Red    #Here we spcify which side and color for center Facelet\n\
                       Left         #Hey you reached last point\n";
    std::string letter;
    std::stringstream ss(str);
    next(ss,letter);

    Color col;
    assertColor(ss,col);
    EXPECT_EQ(Red,  col);

    EXPECT_THROW(assertColor(ss,col), std::runtime_error);  //Due to finding a letter that doesn't specify a Color i.e. 'L' (in Left)
    EXPECT_THROW(assertColor(ss,col), std::runtime_error);  //Due to stream exhaustion
}


TEST(input, assertFaceSide){
    std::string str = "\
                       #Following is an example of sample Face specification\n\
                       \
                       Left white   #Hey you reached last point\n";
    std::string letter;
    std::stringstream ss(str);
    
    FaceSide fs;
    assertFaceSide(ss, fs);
    EXPECT_EQ(Left, fs);

    EXPECT_THROW(assertFaceSide(ss, fs), std::runtime_error); //Due to finding a letter that doesn't specify a FaceSide i.e. 'w' (in white
    EXPECT_THROW(assertFaceSide(ss, fs), std::runtime_error); //Due to stream exhaustion
}


TEST_F(OverloadingTest, basics) {
    /* === Testing overloaded 'operator*' ===
     * Call to operator* makes call to 'operator*='
     * So need to test it explicitly
     */
    ///Front first
    EXPECT_EQ(up, front*right);
    EXPECT_EQ(down, front*left);
    EXPECT_EQ(left, front*up);
    EXPECT_EQ(right, front*down);

    ///Back first
    EXPECT_EQ(down, back*right);
    EXPECT_EQ(up, back*left);
    EXPECT_EQ(right, back*up);
    EXPECT_EQ(left, back*down);

    ///Right first
    EXPECT_EQ(down, right*front);
    EXPECT_EQ(up, right*back);
    EXPECT_EQ(front, right*up);
    EXPECT_EQ(back, right*down);

    ///Left first
    EXPECT_EQ(up, left*front);
    EXPECT_EQ(down, left*back);
    EXPECT_EQ(back, left*up);
    EXPECT_EQ(front, left*down);

    ///Up first
    EXPECT_EQ(right, up*front);
    EXPECT_EQ(left, up*back);
    EXPECT_EQ(front, up*left);
    EXPECT_EQ(back, up*right);

    ///Down first
    EXPECT_EQ(left, down*front);
    EXPECT_EQ(right, down*back);
    EXPECT_EQ(back, down*left);
    EXPECT_EQ(front, down*right);

}

TEST_F(OverloadingTest, compoundassignment){
    EXPECT_EQ(left, f_front);
    EXPECT_EQ(back, f_up);
    EXPECT_EQ(down, f_right);
}

TEST_F(OverloadingTest, check) {
    ///Same FaceSide
    EXPECT_EQ(front, front*front);
    ///Opposite FaceSide
    EXPECT_EQ(up, up*down);
    ///
    EXPECT_EQ(undefside, undefside*down);
    ///F_UNDEFINED FaceSide
    EXPECT_NO_THROW(right*undefside);

}

/* =============== Untested Functions ===============
 * Following functions declared in "common.h" are not
 * tested as they are for debug purpose and does not
 * affect overall program logic
 * 1. void handler(int sig)
 * 2. printAllColor()
 * 3. printAllFaceSide()
 * 4. colorFormat()
 * ==================================================
 */
