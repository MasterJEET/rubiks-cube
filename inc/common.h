/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 14th Apr 2017
 *
 * */

#ifndef COMMON_H
#define COMMON_H
#include <ostream>

#   if __STDC_VERSION__ < 199901L
#    if __GNUC__ >= 2
#     define __func__ __FUNCTION__
#    else
#     define __func__ "<unknown>"
#    endif
#   endif

enum Color {
#   define X(a) a
#   include "Color.def"
#   undef X
};

enum FaceSide {
#   define X(a) a
#   include "FaceSide.def"
#   undef X
};

enum PositionType {
#   define X(a) a
#   include "PositionType.def"
#   undef X
};

extern const char *Color_str[];

extern const char *FaceSide_str[];

extern const char *PositionType_str[];

extern std::ostream& operator <<(std::ostream& os, Color);

extern std::ostream& operator <<(std::ostream& os, FaceSide);

extern std::ostream& operator <<(std::ostream& os, PositionType);

bool areOpposite(FaceSide first, FaceSide second);                          //Check if given pair of FaceSides are opposite of each other
bool anyOpposite(FaceSide first, FaceSide second, FaceSide third);          //Check if any of the given FaceSides form opposite FaceSides

#endif
