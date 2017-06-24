/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 17th Jun 2017
 *
 * */

//First google test ever
#include "gtest/gtest.h"
#include "common.h"


TEST(cubecell, faceside) {
    /* === For checking overloaded operator "<<" for FaceSide ===
     * Since these overloaded operators use FaceSide_str[] array
     * this testcase inherently validates it as well
     * === ===
     */

    // string stream for writing FaceSide into it using "<<"
    std::stringstream ss;
    
    ss << front;
    EXPECT_EQ("Front", ss.str());
    ss.str("");
    
    ss << back;
    EXPECT_EQ("Back", ss.str());
    ss.str("");
    
    ss << left;
    EXPECT_EQ("Left", ss.str());
    ss.str("");
    
    ss << right;
    EXPECT_EQ("Right", ss.str());
    ss.str("");
    
    ss << up;
    EXPECT_EQ("Up", ss.str());
    ss.str("");
    
    ss << down;
    EXPECT_EQ("Down", ss.str());
    ss.str("");

    ss << undefside;
    EXPECT_EQ("F_UNDEFINED",ss.str());
}

TEST(cubecell, color) {
    /* === For checking overloaded operator "<<" for Color ===
     * Since these overloaded operators use Color_str[] array
     * this testcase inherently validates it as well
     * === ===
     */

    // string stream for writing Color into it using "<<"
    std::stringstream ss;
    // string to be retrieved from string stream
    std::string col;

    ss << red;
    EXPECT_EQ("Red",ss.str());
    ss.str("");

    ss << white;
    EXPECT_EQ("White",ss.str());
    ss.str("");

    ss << yellow;
    EXPECT_EQ("Yellow",ss.str());
    ss.str("");

    ss << green;
    EXPECT_EQ("Green",ss.str());
    ss.str("");

    ss << blue;
    EXPECT_EQ("Blue",ss.str());
    ss.str("");

    ss << orange;
    EXPECT_EQ("Orange",ss.str());
    ss.str("");

    ss << undefcol;
    EXPECT_EQ("C_UNDEFINED",ss.str());
}


TEST(cubecell, positiontype) {
    /* === For checking overloaded operator "<<" for PositionType ===
     * Since these overloaded operators use PositionType_str[] array
     * this testcase inherently validates it as well
     * === ===
     */

    // string stream for writing PositionType into it using "<<"
    std::stringstream ss;
    // string to be retrieved from string stream
    std::string type;

    ss << center;
    EXPECT_EQ("Center",ss.str());
    ss.str("");

    ss << edge;
    EXPECT_EQ("Edge",ss.str());
    ss.str("");

    ss << corner;
    EXPECT_EQ("Corner",ss.str());
    ss.str("");

    ss << undeftype;
    EXPECT_EQ("P_UNDEFINED",ss.str());
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
     * don't need to tested explicitly
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

/* =============== Untested Functions ===============
 * Following functions declared in "common.h" are not
 * tested as they are for debug purpose and does not
 * affect overall program logic
 * 1. void handler(int sig)
 * 2. printAllColor()
 * 3. printAllFaceSide()
 * ==================================================
 */
