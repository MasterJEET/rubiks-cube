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
        
    if(_vecSide.size() > 3){
        throw std::runtime_error(__func__ + std::string(": Number of FaceSides should be at most three for a Position specification"));
    }


    if(_vecSide[0] == undefside)
        throw std::runtime_error(__func__ + std::string(": First FaceSide cannot be undefside."));

    //Keeping undefside to last
    if(_vecSide[1] == undefside && _vecSide[2] != undefside)
        std::iter_swap(vecSide.begin()+1, vecSide.begin()+2);

    if(_vecSide[1] == undefside && _vecSide[2] == undefside)
        ptype = center;

    if(_vecSide[1] != undefside && _vecSide[2] == undefside){
        if(areOpposite(_vecSide[1], _vecSide[2]))
            throw std::runtime_error(__func__ + std::string(": Pair of FaceSides contain opposite faces."));
        ptype = edge;
    }

    if(_vecSide[1] != undefside && _vecSide[2] != undefside){
        if(anyOpposite(_vecSide[0], _vecSide[1], _vecSide[2]))
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
