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
#   define X(a,b) b,
const char *Color_str[] = {
#   include "Color.def"
    "C_UNDEFINED"
};
#   undef X

#   define X(a,b) #a,
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



bool next(std::istream& is, std::string& letter){

    while(is){

        //Skipping whitespace if any
        is >> std::ws;
        if(is.peek() == '#'){
            is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }

        if(is >> letter){

            //Making it case insensitive , one can provide "red" or "Red"
            //instead of "R" to indicate Color red 
            letter = toupper(letter[0]);

            return true;
        }
    }

    //Execution reached here means the letter/word could NOT be extracted
    return false;
};



void assertColor(std::istream& is, Color& col){

    std::string l;
    if(!next(is, l))
        throw std::runtime_error("Cannot read Color from input. Please make sure to\
                provide all required information to construct a Cube.\
                Refer \"Cube.dat\" and \"<to be added>\" for sample input.");

    if(!ColorFromLetter(l, col))
        throw std::runtime_error("Invalid Color specification found:\
                check b in X(a,b) of \"Color.def\" for allowed valid arguments.\
                Refer \"Cube.dat\" and \"<to be added>\" for sample input.");
};



void assertFaceSide(std::istream& is, FaceSide& fs){

    std::string l;
    if(!next(is, l))
        throw std::runtime_error("Cannot read FaceSide from input. Please make sure to\
                provide all required information to construct a Cube.\
                Refer \"Cube.dat\" and \"<to be added>\" for sample input.");

    if(!FaceSideFromLetter(l, fs))
        throw std::runtime_error("Invalid FaceSide specification found:\
                check b in X(a,b) of \"Color.def\" for allowed valid arguments.\
                Refer \"Cube.dat\" and \"<to be added>\" for sample input.");
};



FaceSide& operator*=(FaceSide& lhs, const FaceSide& rhs){

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

    //Executin reached here it means either lhs == rhs or lhs is opposite of rhs
    //In both case return lhs
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

FaceSide opposite(const FaceSide& fs){
    switch(fs){
        case front:
            return back;
        case back:
            return front;
        case up:
            return down;
        case down:
            return up;
        case left:
            return right;
        case right:
            return left;
        default:
            return undefside;
    }

    //Execution will never reach here
    return undefside;
}

void setEquivalentFaceSide(const FaceSide& f,FaceSide& u,FaceSide& r,FaceSide& d,FaceSide& l){

    switch(f){
        case Front:
            u = up; r = right; d = down; l = left;
            break;
        case Back:
            u = up; r = left; d = down; l = right;
            break;
        case Right:
            u = up; r = back; d = down; l = front;
            break;
        case Left:
            u = up; r = front; d = down; l = back;
            break;
        case Up:
            u = back; r = right; d = front; l = left;
            break;
        case Down:
            u = front; r = right; d = back; l = left;
            break;
        default:
            break;
    }

};


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



bool ColorFromLetter(const char c, Color& col){
    std::string s = &c;
    return ColorFromLetter(s,col);
};


bool ColorFromLetter(const std::string& s, Color& col){
    createmapColor();
    auto it = toColor.find(s);
    if(it == toColor.end())
        return false;
    col = it->second;
    return true;
};

bool FaceSideFromLetter(const char c, FaceSide& fs){
    std::string s = &c;
    return FaceSideFromLetter(s,fs);
};

bool FaceSideFromLetter(const std::string& s, FaceSide& fs){
    createmapFaceSide();
    auto it = toFaceSide.find(s);
    if(it == toFaceSide.end())
        return false;
    fs = it->second;
    return true;
        //throw std::invalid_argument("Invalid Argument: check b in X(a,b) of \"FaceSide.def\" for allowed arguments");
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
