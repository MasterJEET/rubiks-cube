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

TEST(cubemetabolism, overloading) {
    /* === Testing overloaded 'operator*' ===
     * Call to operator* makes call to 'operator*='
     * So need to test it explicitly
     */
    EXPECT_EQ(up, front*right);
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
