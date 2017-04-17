/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 15th Apr 2017
 *
 * */

#include "common.h"

const char *Color_str[] = {
#   define X(a) #a
#   include "Color.def"
#   undef X
};

const char *FaceSide_str[] = {
#   define X(a) #a
#   include "FaceSide.def"
#   undef X
};

const char *PositionType_str[] = {
#   define X(a) #a
#   include "PositionType.def"
#   undef X
};

std::ostream& operator <<(std::ostream& os, Color col){
    return os << Color_str[col];
};

std::ostream& operator <<(std::ostream& os, FaceSide fac){
    return os << FaceSide_str[fac];
};

std::ostream& operator <<(std::ostream& os, PositionType ptype){
    return os << PositionType_str[ptype];
};

bool areOpposite(FaceSide first, FaceSide second)
{
    if((first == Front && second == Back) || (first == Back && second == Front))
        return true;
    if((first == Up && second == Down) || (first == Down && second == Up))
        return true;
    if((first == Left && second == Right) || (first == Right && second == Left))
        return true;
    return false;
}

bool anyOpposite(FaceSide first, FaceSide second, FaceSide third)
{
    return (areOpposite(first, second) || areOpposite(first, third) || areOpposite(second, third));
}
