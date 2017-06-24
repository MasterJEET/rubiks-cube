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
