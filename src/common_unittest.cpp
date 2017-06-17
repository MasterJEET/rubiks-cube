//First google test ever
#include "gtest/gtest.h"
#include "common.h"

//All facesides
const FaceSide front = Front;
const FaceSide back = Back;
const FaceSide left = Left;
const FaceSide right = Right;
const FaceSide up = Up;
const FaceSide down = Down;
const FaceSide undefside = F_UNDEFINED;

//All colors
const Color white = White;
const Color yellow = Yellow;
const Color orange = Orange;
const Color red = Red;
const Color green = Green;
const Color blue = Blue;
const Color undefcol = C_UNDEFINED;

//All Position types
const PositionType center = Center;
const PositionType edge = Edge;
const PositionType corner = Corner;
const PositionType undeftype = P_UNDEFINED;


TEST(cubecell, faceside) {
    /* === For checking overloaded operator "<<" for FaceSide ===
     * Since these overloaded operators use FaceSide_str[] array
     * this testcase inherently validates it as well
     * === ===
     */

    // string stream for writing FaceSide into it using "<<"
    std::stringstream ss;
    // string to be retrieved from string stream
    std::string side;
    
    ss << front;
    ss >> side;
    EXPECT_EQ("Front", side);
    ss.str("");
    ss.clear();
    
    ss << back;
    ss >> side >> side;
    EXPECT_EQ("Back", side);
    ss.str("");
    ss.clear();
    
    ss << left;
    ss >> side;
    EXPECT_EQ("Left", side);
    ss.str("");
    ss.clear();
    
    ss << right;
    ss >> side;
    EXPECT_EQ("Right", side);
    ss.str("");
    ss.clear();
    
    ss << up;
    ss >> side;
    EXPECT_EQ("Up", side);
    ss.str("");
    ss.clear();
    
    ss << down;
    ss >> side;
    EXPECT_EQ("Down", side);
    ss.str("");
    ss.clear();

    ss << undefside;
    ss >> side;
    EXPECT_EQ("F_UNDEFINED",side);
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
    ss >> col;
    EXPECT_EQ("Red",col);
    ss.str("");
    ss.clear();

    ss << white;
    ss >> col;
    EXPECT_EQ("White",col);
    ss.str("");
    ss.clear();

    ss << yellow;
    ss >> col;
    EXPECT_EQ("Yellow",col);
    ss.str("");
    ss.clear();

    ss << green;
    ss >> col;
    EXPECT_EQ("Green",col);
    ss.str("");
    ss.clear();

    ss << blue;
    ss >> col;
    EXPECT_EQ("Blue",col);
    ss.str("");
    ss.clear();

    ss << orange;
    ss >> col;
    EXPECT_EQ("Orange",col);
    ss.str("");
    ss.clear();

    ss << undefcol;
    ss >> col;
    EXPECT_EQ("C_UNDEFINED",col);
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
    ss >> type;
    EXPECT_EQ("Center",type);
    ss.str("");
    ss.clear();

    ss << edge;
    ss >> type;
    EXPECT_EQ("Edge",type);
    ss.str("");
    ss.clear();

    ss << corner;
    ss >> type;
    EXPECT_EQ("Corner",type);
    ss.str("");
    ss.clear();

    ss << undeftype;
    ss >> type;
    EXPECT_EQ("P_UNDEFINED",type);
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
