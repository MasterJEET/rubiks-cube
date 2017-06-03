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

//============ Define enum start ===========
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
//=========== Define enum end =============

extern const char *Color_str[];

extern const char *FaceSide_str[];

extern const char *PositionType_str[];

extern std::ostream& operator <<(std::ostream& os, Color);

extern std::ostream& operator <<(std::ostream& os, FaceSide);

extern std::ostream& operator <<(std::ostream& os, PositionType);

bool areOpposite(FaceSide* first, FaceSide* second);                          //Check if given pair of FaceSides are opposite of each other
bool anyOpposite(FaceSide* first, FaceSide* second, FaceSide* third);          //Check if any of the given FaceSides form opposite FaceSides

extern void createmapColor();
extern void createmapFaceSide();

extern Color ColorFromStr(std::string col);
extern FaceSide FaceSideFromStr(std::string fs);

//SIGTERM handler
void handler(int sig);

//Print all elements of toColor map
void printAllColor();

//Print all elemensts of toFaceSide map
void printAllFaceSide();

#endif
