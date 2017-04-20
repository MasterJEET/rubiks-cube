/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 15th Apr 2017
 *
 * */

#include "common.h"

std::map<std::string, Color> toColor;                                                   //Maps first letter of Color to Color itself
std::map<std::string, FaceSide> toFaceSide;                                             //Maps first letter of FaceSide to FaceSide itself

//============ Define <index,type> pair start ===========
#   define X(a,b) #a,
const char *Color_str[] = {
#   include "Color.def"
    "C_UNDEFINED"
};

const char *FaceSide_str[] = {
#   include "FaceSide.def"
    "F_UNDEFINED"
};

const char *PositionType_str[] = {
#   include "PositionType.def"
    "P_UNDEFINED"
};
#   undef X
//==================== Define end ======================

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

//======== Create maps | Start =========
void createmapColor(){
    if(!toColor.size())
        return;
#   define X(a,b)   toColor.insert( std::pair<std::string,Color>(b,a) );
#   include "Color.def"
#   undef X
}

void createmapFaceSide(){
    if(!toFaceSide.size())
        return;
#   define X(a,b)   toFaceSide.insert( std::pair<std::string,FaceSide>(b,a) );
#   include "FaceSide.def"
#   undef X
}
//======== Create maps | End =========



Color ColorFromStr(std::string col){
    return toColor[col];
};

FaceSide FaceSideFromStr(std::string fs){
    auto it = toFaceSide.find(fs);
    if(it == toFaceSide.end())
        return F_UNDEFINED;
    return it->second;
};
