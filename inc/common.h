/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 14th Apr 2017
 *
 * */

#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <map>
#include <sstream>
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>

#   if __STDC_VERSION__ < 199901L
#    if __GNUC__ >= 2
#     define __func__ __FUNCTION__
#    else
#     define __func__ "<unknown>"
#    endif
#   endif

///============ Define enum start ===========
#   define X(a,b) a,
enum Color {
#   include "Color.def"
    C_UNDEFINED
};

enum FaceSide {
#   include "FaceSide.def"
    F_UNDEFINED
};

enum PositionType {
#   include "PositionType.def"
    P_UNDEFINED
};
#   undef X
///=========== Define enum end =============

extern const char *Color_str[];

extern const char *FaceSide_str[];

extern const char *PositionType_str[];

extern std::ostream& operator <<(std::ostream& os, Color);

extern std::ostream& operator <<(std::ostream& os, FaceSide);

extern std::ostream& operator <<(std::ostream& os, PositionType);

///Overloding to implement cross multiplication similar to those for
///Cartesian coordinates (Right hand system), compund assignment
FaceSide& operator*=(FaceSide& lhs, const FaceSide& rhs);

///Overloading multiplication
FaceSide operator*(FaceSide lhs, const FaceSide& rhs);

///Check if given pair of FaceSides are opposite of each other
bool areOpposite(const FaceSide first,const FaceSide second);

///Check if any of the given FaceSides form opposite FaceSides
bool anyOpposite(const FaceSide first,const FaceSide second,const FaceSide third);

extern void createmapColor();
extern void createmapFaceSide();

extern Color ColorFromLetter(char col);
extern Color ColorFromLetter(std::string col);
extern FaceSide FaceSideFromLetter(char fs);
extern FaceSide FaceSideFromLetter(std::string fs);

///SIGTERM handler
void handler(int sig);

///Colored output format for Color
std::string colorFormat(const Color col);

///Print all elements of toColor map
void printAllColor();

///Print all elemensts of toFaceSide map
void printAllFaceSide();

/// Basic checks and setting before program starts
std::string getHome();


/// ======== Global Constants Definition ========
///All facesides
const FaceSide front = Front;
const FaceSide back = Back;
const FaceSide left = Left;
const FaceSide right = Right;
const FaceSide up = Up;
const FaceSide down = Down;
const FaceSide undefside = F_UNDEFINED;

///All colors
const Color white = White;
const Color yellow = Yellow;
const Color orange = Orange;
const Color red = Red;
const Color green = Green;
const Color blue = Blue;
const Color undefcol = C_UNDEFINED;

///All Position types
const PositionType center = Center;
const PositionType edge = Edge;
const PositionType corner = Corner;
const PositionType undeftype = P_UNDEFINED;

///Path where all of rubkis-cube's civilization is present
extern const std::string CUBE_HOME;

/// =============================================

#endif
