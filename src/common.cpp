/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 15th Apr 2017
 *
 * */

#include "common.h"
#include <unordered_map>
#include <stdexcept>

std::unordered_map<std::string, Color> toColor;                                                   //Maps first letter of Color to Color itself
std::unordered_map<std::string, FaceSide> toFaceSide;                                             //Maps first letter of FaceSide to FaceSide itself

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

FaceSide& operator*=(FaceSide& lhs, const FaceSide& rhs){

    if(lhs == rhs)
        throw std::runtime_error("Cannot multiply same FaceSide...");
    
    if( areOpposite(lhs, rhs))
        throw std::runtime_error("Cannot multiply opposite FaceSide...");

    //Handling undefside
    if( lhs == F_UNDEFINED || rhs == F_UNDEFINED ){ lhs = undefside; return lhs;}

    //Front lhs
    if(lhs == front && rhs == right){ lhs = up; return lhs; }
    if(lhs == front && rhs == left){ lhs = down; return lhs; }
    if(lhs == front && rhs == up){ lhs = left; return lhs; }
    if(lhs == front && rhs == down){ lhs = right; return lhs; }

    //Back lhs
    if(lhs == back && rhs == right){ lhs = down; return lhs; }
    if(lhs == back && rhs == left){ lhs = up; return lhs; }
    if(lhs == back && rhs == up){ lhs = right; return lhs; }
    if(lhs == back && rhs == down){ lhs = left; return lhs; }

    //Right lhs
    if(lhs == right && rhs == front){ lhs = down; return lhs; }
    if(lhs == right && rhs == back){ lhs = up; return lhs; }
    if(lhs == right && rhs == up){ lhs = front; return lhs; }
    if(lhs == right && rhs == down){ lhs = back; return lhs; }

    //Left lhs
    if(lhs == left && rhs == front){ lhs = up; return lhs; }
    if(lhs == left && rhs == back){ lhs = down; return lhs; }
    if(lhs == left && rhs == up){ lhs = back; return lhs; }
    if(lhs == left && rhs == down){ lhs = front; return lhs; }

    //Up lhs
    if(lhs == up && rhs == front){ lhs = right; return lhs; }
    if(lhs == up && rhs == back){ lhs = left; return lhs; }
    if(lhs == up && rhs == right){ lhs = back; return lhs; }
    if(lhs == up && rhs == left){ lhs = front; return lhs; }

    //Down lhs
    if(lhs == down && rhs == front){ lhs = left; return lhs; }
    if(lhs == down && rhs == back){ lhs = right; return lhs; }
    if(lhs == down && rhs == right){ lhs = front; return lhs; }
    if(lhs == down && rhs == left){ lhs = back; return lhs; }

    //Kept to suppress compiler warnings, else following return statement
    //is not required, function execution should not reach here
    return lhs;
};

FaceSide operator*(FaceSide lhs, const FaceSide& rhs){
    lhs *= rhs;
    return lhs;
};

bool areOpposite(const FaceSide first,const FaceSide second)
{
    if((first == Front && second == Back) || (first == Back && second == Front))
        return true;
    if((first == Up && second == Down) || (first == Down && second == Up))
        return true;
    if((first == Left && second == Right) || (first == Right && second == Left))
        return true;
    return false;
}

bool anyOpposite(const FaceSide first,const FaceSide second,const FaceSide third)
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



Color ColorFromLetter(char col) {
    std::string s_col = &col;
    return ColorFromLetter(s_col);
};


Color ColorFromLetter(std::string col){
    createmapColor();
    auto it = toColor.find(col);
    if(it == toColor.end())
        throw std::invalid_argument("Invalid Argument: check b in X(a,b) of \"Color.def\" for allowed valid arguments");
    return it->second;
};

FaceSide FaceSideFromLetter(char fac) {
    std::string s_fac = &fac;
    return FaceSideFromLetter(s_fac);
};

FaceSide FaceSideFromLetter(std::string fac){
    createmapFaceSide();
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

std::string getHome(){
    char* cube_home = std::getenv("CUBE_HOME");
    if(cube_home)
        return std::string( cube_home );
    else
        return std::string( std::getenv("HOME") + std::string("/rubiks-cube"));
};
