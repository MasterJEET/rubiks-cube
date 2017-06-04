/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 15th Apr 2017
 *
 * */

#include "common.h"
#include <stdexcept>

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

bool areOpposite(const FaceSide *first,const FaceSide *second)
{
    if((*first == Front && *second == Back) || (*first == Back && *second == Front))
        return true;
    if((*first == Up && *second == Down) || (*first == Down && *second == Up))
        return true;
    if((*first == Left && *second == Right) || (*first == Right && *second == Left))
        return true;
    return false;
}

bool anyOpposite(const FaceSide *first,const FaceSide *second,const FaceSide *third)
{
    return (areOpposite(first, second) || areOpposite(first, third) || areOpposite(second, third));
}

//======== Create maps | Start =========
void createmapColor(){
    if(toColor.size())
        return;
#   define X(a,b)   toColor.insert( std::pair<std::string,Color>(b,a) );
#   include "Color.def"
#   undef X
}

void createmapFaceSide(){
    if(toFaceSide.size())
        return;
#   define X(a,b)   toFaceSide.insert( std::pair<std::string,FaceSide>(b,a) );
#   include "FaceSide.def"
#   undef X
}
//======== Create maps | End =========



Color ColorFromStr(std::string col){
    auto it = toColor.find(col);
    if(it == toColor.end())
        throw std::invalid_argument("Invalid Argument: check b in X(a,b) of \"Color.def\" for allowed valid arguments");
    return it->second;
};

FaceSide FaceSideFromStr(std::string fac){
    auto it = toFaceSide.find(fac);
    if(it == toFaceSide.end())
        throw std::invalid_argument("Invalid Argument: check b in X(a,b) of \"FaceSide.def\" for allowed arguments");
    return it->second;
};

//Handler for signal SIGABRT
void handler(int sig) {
      void *array[20];
        size_t size;

          // get void*'s for all entries on the stack
          size = backtrace(array, 20);
          
          // print out all the frames to stderr
          fprintf(stderr, "Error: signal %d:\n", sig);
          backtrace_symbols_fd(array, size, STDERR_FILENO);
          exit(1);
};

void printAllColor(){
    createmapColor();
    std::cout << "======= Colors | start =======" << std::endl;
    for(auto& it: toColor)
        std::cout << it.first << " --> " << it.second << std::endl;
    std::cout << "======== Colors | end ========" << std::endl;
};

void printAllFaceSide(){
    createmapFaceSide();
    std::cout << "====== FaceSide | start ======" << std::endl;
    for(auto& it: toFaceSide)
        std::cout << it.first << " --> " << it.second << std::endl;
    std::cout << "======= FaceSide | end =======" << std::endl;
};
