/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "position.h"
#include <iostream>
#include <algorithm>


Position::Position(const std::vector<FaceSide> _vecSide):vecSide(_vecSide){
        
    if(vecSide.size() > 3){
        throw std::runtime_error(__func__ + std::string(": Number of FaceSides should be at most three for a Position specification"));
    }


    if(vecSide[0] == undefside)
        throw std::runtime_error(__func__ + std::string(": First FaceSide cannot be undefside."));

    //Keeping undefside to last
    if(vecSide[1] == undefside && vecSide[2] != undefside)
        std::iter_swap(vecSide.begin()+1, vecSide.begin()+2);

    if(vecSide[1] == undefside && vecSide[2] == undefside)
        ptype = center;

    if(vecSide[1] != undefside && vecSide[2] == undefside){
        if(areOpposite(vecSide[1], vecSide[2]))
            throw std::runtime_error(__func__ + std::string(": Pair of FaceSides contain opposite faces."));
        ptype = edge;
    }

    if(vecSide[1] != undefside && vecSide[2] != undefside){
        if(anyOpposite(vecSide[0], vecSide[1], vecSide[2]))
            throw std::runtime_error(__func__ + std::string(": Triplet of FaceSides contain opposite faces."));
        ptype = corner;
    }

}

FaceSide Position::getSideAt(size_t index) const{
    if(index > 2 )
        throw std::runtime_error(__func__ + std::string(": There are only three allowed values for index: 0 , 1 & 2 whereas " + std::to_string(index) + std::string(" was provided")));
    if(index >= vecSide.size())
        return undefside;
    return vecSide.at(index);
};

//template<typename T> T& Position::operator*=(const FaceSide& rhs){
//    switch( vecSide.size() ) {
//        case 1:
//            return *this;
//        case 2:
//            vecSide[1] *= rhs;
//            return *this;
//    }
//}

///template Position& Position::operator*=(const FaceSide& rhs);

std::ostream& operator<<(std::ostream& os, Position P){
    os << "Position: ptype = " << P.ptype;
    os << ", vecSide = { ";
    for(const auto& face : P.vecSide){
        if(face != undefside)
            os << face << " ";
    }
    os << "}";
    return os;
}



/** ================= operator overloading ================
 *
 *  This doesn't apply here anymore.
 *  This condition has been implemented for FaceletPosition
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
 *
 *   Position P1(front, left); //One more FaceSide required \
 *                             Assume F_UNDEFINED appended \
 *                             to FaceSide vecotr of object P1
 *
 *   Position P2(front); ///Similarly two more required
 *
 * 2. Now all Position objects can be assumed to have FaceSide
 *   number equal to three. Two Position objects are equal if
 *   and only if they satisfy both 'a' and 'b'
 *
 *      a. Their first FaceSides are equal i.e.
 *          P1.firstFS == P2.firstFS
 *
 *      b. 2nd and 3rd FS of 1st and 2nd are equal OR
 *         2nd and 3rd FS 1st P are equal with 3rd and 2nd FS of
 *         2nd P respectively
 *
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
    if(rhs == undefside )
        throw std::runtime_error(__func__ + std::string(": Position multiplication with undefside is not allowed"));
    for(auto& el:vecSide){
        el *= rhs;
    }    
    return *this;
}
