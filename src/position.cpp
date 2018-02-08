/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "position.h"
#include <iostream>
#include <algorithm>

std::ostream& operator<<(std::ostream &os, Step S)
{
    os << "side: " << S.f << ", is_clockwise: " << S.is_clockwise << ", no_of_turns: " << S.no_of_turns \
        << ", is_mid: " << S.is_mid ;
    return os;
}

Position::Position(const std::vector<FaceSide> _vecSide):vecSide(_vecSide){
        
    if(vecSide.size() > 3 || vecSide.size() == 0){
        throw std::runtime_error(__func__ +\
                std::string(": Number of FaceSides should be at most three and at least one."));
    }


    if(vecSide[0] == undefside)
        throw std::runtime_error(__func__ + std::string(": First FaceSide cannot be undefside."));

    //In case of two or three elements present in vecSide, append undefside
    while(vecSide.size() != 3)
        vecSide.push_back(undefside);


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
        throw std::runtime_error(__func__ + std::string(": There are only three allowed values for index: 0 , 1 & 2 whereas "\
                    + std::to_string(index) + std::string(" was provided.")));
    if(index >= vecSide.size())
        return undefside;
    return vecSide.at(index);
}


std::size_t Position::size() const{
    std::size_t size = 0;
    for(auto &fs: vecSide){
        if(fs != undefside)
            size ++;
    }
    return size;
}


Position Position::getRelativePosition(const FaceSide& f) const{
    std::vector<FaceSide> vFS;
    for(const auto& fs: vecSide)
        vFS.push_back( getRelativeFaceSide(fs, f) );

    return vFS;
}

bool Position::willGetAffected(Step s) const
{
    ///If faceside is not defined then roatation itself is not defined, return false
    if(s.f == undefside)
        return false;

    ///Return true when Position is on the Face being roated
    if(s.is_mid==false && isOn(s.f))
        return true;

    ///Return true when Position is on the Middle layer being roated
    if(s.is_mid==true && !isOn(s.f) && !isOn( opposite(s.f) ))
        return true;

    ///Other wise return false
    return false;
}

Position Position::ifRotated(StepSequence seq) const
{
    Position pRet(vecSide);

    for(const auto& s: seq)
        for(std::size_t turns = 1; turns <= s.no_of_turns; turns++)
            if(s.f != undefside && pRet.willGetAffected(s))
                pRet *= (s.is_clockwise ? s.f : opposite(s.f) );

    return pRet;
}


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
