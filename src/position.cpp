/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "position.h"
#include <iostream>

Position::Position(){};

Position::Position(const FaceSide first): vecSide{first}, ptype(Center){
        //Noting for now
}

Position::Position(const FaceSide first,const FaceSide second): vecSide{first, second}, ptype(Edge){
    if(areOpposite(first, second))
        throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
}

Position::Position(const FaceSide first,const FaceSide second,const FaceSide third): vecSide{first, second, third}, ptype(Corner){
    if(anyOpposite(first, second, third))
        throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
}

PositionType Position::getPositionType() const
{
    return ptype;
}

const std::vector< FaceSide> * Position::getSide() const
{
    return &(this->vecSide);
}

FaceSide Position::getSideAt(size_t index) const{
    if(index < vecSide.size())
        return vecSide.at(index);
    return F_UNDEFINED;
};

std::ostream& operator<<(std::ostream& os, Position P){
    os << "Position: ptype = " << P.getPositionType();
    auto pvecSide = P.getSide();
    os << ", vecSide = { ";
    for(const auto& face : *pvecSide){
        os << face << " ";
    }
    os << "}";
    return os;
}



/* ================= operator== overloading ================
 * Required for Implemention of std::unordered_map with 
 * Position as key
 *
 * The equality of two Position objects are derived as follows
 *
 * P : Position
 * FS: FaceSide
 *
 * 1. Consider required number of F_UNDEFINED FaceSides to be
 *   be part of Position object so that total number of FaceSides
 *   Position becomes three
 *   e.g. if we have
 *   Position P1(front, left); //One more FaceSide required
 *                             //Assume F_UNDEFINED appended
 *                             //to FaceSide vecotr of object P1
 *   Position P2(front); //Similarly two more required
 *
 * 2. Now all Position objects can be assumed to have FaceSide
 *   number equal to three. Two Position objects are equal if
 *   and only if they satisfy both 'a' and 'b'
 *      a. Their first FaceSides are equal i.e.
 *          P1.firstFS == P2.firstFS
 *      b. 2nd and 3rd FS of 1st and 2nd are equal OR
 *         2nd and 3rd FS 1st P are equal with 3rd and 2nd FS of
 *         2nd P respectively
 *          i.  P1.secondFS == P2.secondFS AND P1.thirdFS == P2.thirdFS, OR
 *          ii. P1.secondFS == P2.thirdFS AND P1.thirdFS == P2.secondFS
 *
 *
 * =========================================================
 */
bool operator==(const Position& lhs, const Position& rhs){
    
    //First FaceSides must be equal, point 2.a descrived above
    if( lhs.getSideAt(0) != rhs.getSideAt(0) )
        return false;

    //2nd and 3rd FaceSide equal in same order, 2.b.i describe above
    if ( lhs.getSideAt(1) == rhs.getSideAt(1) && lhs.getSideAt(2) == rhs.getSideAt(2) )
        return true;

    //2nd and 3rd FaceSide equal in rever order, 2.b.ii described above
    if ( lhs.getSideAt(1) == rhs.getSideAt(2) && lhs.getSideAt(2) == rhs.getSideAt(1) )
        return true;

    //If above conditions doesn't satisfy return false
    return false;
}
