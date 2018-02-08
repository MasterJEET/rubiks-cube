/*! \file   common.h
 *  \brief  Contains most global functions declarations
 * 
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
#include <list>
#include <vector>
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>
#include <limits>

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


typedef std::list<std::vector<FaceSide>> listVecFaceSide;



extern const char *Color_str[];

extern const char *FaceSide_str[];

extern const char *PositionType_str[];

std::ostream& operator <<(std::ostream& os, Color);

std::ostream& operator <<(std::ostream& os, FaceSide);

std::ostream& operator <<(std::ostream& os, PositionType);



/*! \fn bool next(std::istream& is, std::string& word)
 *  \brief  Fetch next word from input stream
 *
 *  This will skip any comments (#this is comment) presnt at start of or in the line.
 *  Set next word in stream to word argumnet.
 *
 *  Return:
 *      *   true    : if parameter 'word' was set successfully
 *      *   false   : otherwise i.e. stream exausted (or only comments left)
 *
 * */
bool next(std::istream& is, std::string& letter);


/*! \fn void assertColor(std::istream& is, Color& col)
 *  \brief  get next word representing a Color, if failed throw runtime error
 *
 * */
void assertColor(std::istream& is, Color& col);


/*! \fn void assertFaceSide(std::istream& is, FaceSide& fs)
 *  \brief  get next word representing a FaceSide, if failed throw runtime error
 *
 * */
void assertFaceSide(std::istream& is, FaceSide& fs);


/*! \fn listVecFaceSide getEdgeFaceSide()
 *  \brief  get list of vector of FaceSide specifying Edge Cubelet positions
 *
 *  Edge Cubelet position can be specified with two FaceSides.
 *  Such as {front, right} , {up, left} and so on. This function returns list of all
 *  such permutations.
 *
 * */
listVecFaceSide getEdgeFaceSide();


/*! \fn listVecFaceSide getCornerFaceSide()
 *  \brief  get list of vector of FaceSide specifying Corner Cubelet positions
 *
 *  Corner Cubelet position can be specified with three FaceSides.
 *  Such as {front, right, up} , {up, left, front} and so on. This function returns list of all
 *  such combinations.
 *
 * */
listVecFaceSide getCornerFaceSide();


/*! \fn FaceSide& operator*=(FaceSide& lhs, const FaceSide& rhs)
 *  \brief  Overloding to implement cross multiplication similar to those for
 *  Cartesian coordinates (Right hand system), compund assignment
 *
 * */
FaceSide& operator*=(FaceSide& lhs, const FaceSide& rhs);


/*! \fn FaceSide operator*(FaceSide lhs, const FaceSide& rhs)
 *  \brief  Overloading multiplication
 *
 * */
FaceSide operator*(FaceSide lhs, const FaceSide& rhs);


/*! \fn bool areOpposite(const FaceSide first,const FaceSide second)
 *  \brief  Check if given pair of FaceSides are opposite of each other
 *
 * */
bool areOpposite(const FaceSide first,const FaceSide second);


/*! \fn bool anyOpposite(const FaceSide first,const FaceSide second,const FaceSide third)
 *  \brief  Check if any of the given FaceSides form opposite FaceSides
 *
 * */
bool anyOpposite(const FaceSide first,const FaceSide second,const FaceSide third);


/*! \fn Return opposite FaceSide
 *  \brief  FaceSide opposite(const FaceSide& fs)
 *
 * */
FaceSide opposite(const FaceSide& fs);


/*! \fn bool isValidFaceSide(const std::string& f)
 *  \brief  Returns true if the string (one letter) corresponds to a Valid FaceSide enum
 *
 *  List of string that corresponds to a valid FaceSide:
 *
 *          F   ->  Front,  B   ->  Back,   U   ->  Up
 *          D   ->  Down,   L   ->  Left,   R   ->  Right
 *
 * */
bool isValidFaceSide(const std::string& f);



/*! \fn void setEquivalentFaceSide(const FaceSide& f,FaceSide& u,FaceSide& r,FaceSide& d,FaceSide& l)
 *  \brief  This function assign up, right, down & left equivalence of 'f' to 'u', 'r', 'd' & 'l' respectively.
 *
 * What are equivalent FaceSides?
 *
 * Observe the current orientation of Cube. If a FaceSide 'fs' is in horizontal plane (up or down),
 * rotate the cube about a horizontal axis parallel to front FaceSide till 'fs' coincides with the front.
 * Face i.e. at FaceSide up now was let's say at FaceSide 'up_before'. Then 'up_before' is <i>up</i> equivalent
 * of 'fs'. We write it as:
 *
 *      up( fs ) = up_before
 *
 * For vertical Faces (front,back,right,left) rotate the Cube about a vertical axis till 'fs' coincides
 * with font FaceSide. Use above analogy to derive FaceSide equivalence.
 *
 * Note: for any FaceSide f, f(front) = f
 *
 * Examples: FaceSide equivalence of right
 *      *  up equivalence of right = up(right) = up
 *      *  down(right) = down
 *      *  right(right) = back
 *      *  left(right) = front
 *
 * */
void setEquivalentFaceSide(const FaceSide& f,FaceSide& u,FaceSide& r,FaceSide& d,FaceSide& l);

/*! \fn FaceSide getEquivalentFaceSide(const FaceSide& first, const FaceSide& second)
 *  \brief Return first FaceSide quivalent of second i.e. first(up)
 *
 * */
FaceSide getEquivalentFaceSide(const FaceSide& first, const FaceSide& second);

/*! \fn FaceSide getRelativeFaceSide(const FaceSide& first, const FaceSide& second)
 *  \brief Returns relative orientation of first FaceSide w.r.t. second
 * 
 * What is relative orientation?
 *
 * Relative orientation of any FaceSide <i>x</i> w.r.t. a given FaceSide <i>f</i> is
 * defined as the new FaceSide <i>x_new</i> that <i>x</i> would occupy if FaceSide
 * <i>f</i> is brought to front side following standard methods of rotation ( See
 * rotation defined for function setEquivalentFaceSide in common.h ). Let's denote
 * relative orientation of <i>x</i> w.r.t. FaceSide <i>f</i> as rel(x,f), we can write
 *
 *      rel(x,f) = x_new
 *
 * Note: For any given FaceSide <i>x</i>,
 *      * rel(<i>x</i>, front) = <i>x</i>
 *      * rel(<i>x</i>, <i>x</i>) = front
 *
 * Examples: List relative orientation of left w.r.t. all other FaceSides
 *      * rel(left, front) = left
 *      * rel(left, left) = front
 *      * rel(left, back) = right
 *      * rel(left, up) = left
 *      * rel(left, down) = left
 *      * rel(left, right) = back
 *
 * */
FaceSide getRelativeFaceSide(const FaceSide& first, const FaceSide& second);

void createmapColor();
void createmapFaceSide();

bool ColorFromLetter(const char c, Color& col);
bool ColorFromLetter(const std::string& s, Color& col);
bool FaceSideFromLetter(const char c, FaceSide& fs);
bool FaceSideFromLetter(const std::string& s, FaceSide& fs);


/*! \fn void handler(int sig)
 *  \brief  SIGTERM handler
 *
 * */
void handler(int sig);


/*! \fn void printAllColor()
 *  \brief  Print all elements of toColor map
 *
 * */
void printAllColor();


/*! \fn void printAllFaceSide()
 *  \brief  Print all elemensts of toFaceSide map
 *
 * */
void printAllFaceSide();


/*! \fn std::string getHome()
 *  \brief  Basic checks and setting before program starts
 *
 * */
std::string getHome();


// ======== Global Constants Definition ========
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

//Path where all of rubkis-cube's civilization is present
extern const std::string CUBE_HOME;

// =============================================


#endif
