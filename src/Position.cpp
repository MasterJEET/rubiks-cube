/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "Position.h"
#include <iostream>

Position::Position(const FaceSide *first): vecSide{first}, ptype(Center){
        //Noting for now
}

Position::Position(const FaceSide* first,const FaceSide* second): vecSide{first, second}, ptype(Edge){
    if(areOpposite(first, second))
        throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
}

Position::Position(const FaceSide* first,const FaceSide* second,const FaceSide* third): vecSide{first, second, third}, ptype(Corner){
    if(anyOpposite(first, second, third))
        throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
}

const PositionType * const Position::getPositionType()
{
    return &(this->ptype);
}

const std::vector<const FaceSide *> * const Position::getSide()
{
    return &(this->vecSide);
}

std::ostream& operator<<(std::ostream& os, Position P){
    os << "Position: ptype = " << *P.getPositionType();
    auto pvecSide = P.getSide();
    os << ", vecSide = { ";
    for(const auto& face : *pvecSide){
        os << *face << " ";
    }
    os << "}";
    return os;
}
