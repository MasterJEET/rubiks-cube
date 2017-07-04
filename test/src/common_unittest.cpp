/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 17th Jun 2017
 *
 * */

//First google test ever
#include "gtest/gtest.h"
#include "common.h"
#include "testcommon.h"

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


    EXPECT_PRED_FORMAT2(checkPrint, "Red", red);
    EXPECT_PRED_FORMAT2(checkPrint, "White", white);
    EXPECT_PRED_FORMAT2(checkPrint, "Yellow", yellow);
    EXPECT_PRED_FORMAT2(checkPrint, "Green", green);
    EXPECT_PRED_FORMAT2(checkPrint, "Blue", blue);
    EXPECT_PRED_FORMAT2(checkPrint, "Orange", orange);
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
    EXPECT_EQ(blue, ColorFromLetter(std::string("B")));
    // Color from string literal of single character
    EXPECT_EQ(white, ColorFromLetter("W"));
    // Color from a single character literal
    EXPECT_EQ(green, ColorFromLetter('G'));

    // FaceSide from std::string with single letter
    EXPECT_EQ(down, FaceSideFromLetter(std::string("D")));
    // FaceSide from string literal of single character
    EXPECT_EQ(left, FaceSideFromLetter("L"));
    // FaceSide from a single character literal
    EXPECT_EQ(back, FaceSideFromLetter('B'));

}

TEST_F(OverloadingTest, basics) {
    /* === Testing overloaded 'operator*' ===
     * Call to operator* makes call to 'operator*='
     * So need to test it explicitly
     */
    //Front first
    EXPECT_EQ(up, front*right);
    EXPECT_EQ(down, front*left);
    EXPECT_EQ(left, front*up);
    EXPECT_EQ(right, front*down);

    //Back first
    EXPECT_EQ(down, back*right);
    EXPECT_EQ(up, back*left);
    EXPECT_EQ(right, back*up);
    EXPECT_EQ(left, back*down);

    //Right first
    EXPECT_EQ(down, right*front);
    EXPECT_EQ(up, right*back);
    EXPECT_EQ(front, right*up);
    EXPECT_EQ(back, right*down);

    //Left first
    EXPECT_EQ(up, left*front);
    EXPECT_EQ(down, left*back);
    EXPECT_EQ(back, left*up);
    EXPECT_EQ(front, left*down);

    //Up first
    EXPECT_EQ(right, up*front);
    EXPECT_EQ(left, up*back);
    EXPECT_EQ(front, up*left);
    EXPECT_EQ(back, up*right);

    //Down first
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
    //Same FaceSide
    EXPECT_THROW(front*front, std::runtime_error);
    //Opposite FaceSide
    EXPECT_THROW(up*down, std::runtime_error);
    //F_UNDEFINED FaceSide
    EXPECT_NO_THROW(right*undefside);

}

/* =============== Untested Functions ===============
 * Following functions declared in "common.h" are not
 * tested as they are for debug purpose and does not
 * affect overall program logic
 * 1. void handler(int sig)
 * 2. printAllColor()
 * 3. printAllFaceSide()
 * ==================================================
 */
