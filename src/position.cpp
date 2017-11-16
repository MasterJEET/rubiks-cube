/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "position.h"
#include <iostream>

Position::Position(const FaceSide first,const FaceSide second): vecSide{first, second}, ptype(Edge){
    if(areOpposite(first, second))
        throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
}

Position::Position(const FaceSide first,const FaceSide second,const FaceSide third): vecSide{first, second, third}, ptype(Corner){
    if(anyOpposite(first, second, third))
        throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
}


Position::Position(const std::vector<FaceSide> _vecSide):vecSide(_vecSide){
        
    switch (_vecSide.size()) {
        case 1:
            ptype = center;
            break;
        case 2:
            if(areOpposite(_vecSide[0], _vecSide[1]))
                throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
            ptype = edge;
            break;
        case 3:
            if(anyOpposite(_vecSide[0], _vecSide[1], _vecSide[2]))
                throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
            ptype = corner;
            break;
        default:
            throw std::runtime_error(__func__ + std::string(": std::vector<FaceSide> must satisfy, 0 < size <= 3"));
    }
}

FaceSide Position::getSideAt(size_t index) const{
    if(index < vecSide.size())
        return vecSide.at(index);
    return F_UNDEFINED;
};

///template<typename T> T& Position::operator*=(const FaceSide& rhs){
///    switch( vecSide.size() ) {
///        case 1:
///            return *this;
///        case 2:
///            vecSide[1] *= rhs;
///            return *this;
///    }
///}

///template Position& Position::operator*=(const FaceSide& rhs);

std::ostream& operator<<(std::ostream& os, Position P){
    os << "Position: ptype = " << P.ptype;
    os << ", vecSide = { ";
    for(const auto& face : P.vecSide){
        os << face << " ";
    }
    os << "}";
    return os;
}



/* ================= operator== overloading ================
 * == This doesn't apply here anymore.
 * == This condition has been implemented for FaceletPosition
 * =========================================================
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
 *   Position P1(front, left); ///One more FaceSide required
 *                             ///Assume F_UNDEFINED appended
 *                             ///to FaceSide vecotr of object P1
 *   Position P2(front); ///Similarly two more required
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
    
    if( lhs.getSideAt(0) == rhs.getSideAt(0) && lhs.getSideAt(1) == rhs.getSideAt(1) && lhs.getSideAt(2) == rhs.getSideAt(2) )
        return true;

    return false;
}

Position& Position::operator*=(const FaceSide& rhs){
    for(auto& el:vecSide){
        el *= rhs;
    }    
    return *this;
}
