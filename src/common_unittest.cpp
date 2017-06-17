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

//std::cout << front << " " << back << " " << left << " " << right << " " << up << " " << down << " " << undefside << std::endl;

//All colors
const Color white = White;
const Color yellow = Yellow;
const Color orange = Orange;
const Color red = Red;
const Color green = Green;
const Color blue = Blue;
const Color undefcol = C_UNDEFINED;

//std::cout << white << " " << yellow << " " << orange << " " << red << " " << green << " " << blue << " " << undefcol << std::endl;

//All Position types
const PositionType center = Center;
const PositionType edge = Edge;
const PositionType corner = Corner;
const PositionType undefptype = P_UNDEFINED;

//std::cout << center << " " << edge << " " << corner << " " << undefptype << std::endl;

TEST(testcase1, test1) {
    EXPECT_EQ(1, 1);
}
