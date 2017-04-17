/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "Position.h"
#include <iostream>

Position::Position(FaceSide first): vecSide{first}, ptype(Center){
        //Noting for now
}

Position::Position(FaceSide first, FaceSide second): vecSide{first, second}, ptype(Edge){
    if(areOpposite(first, second))
        throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
}

Position::Position(FaceSide first, FaceSide second, FaceSide third): vecSide{first, second, third}, ptype(Center){
    if(anyOpposite(first, second, third))
        throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
}

const PositionType *Position::getType()
{
    return &(this->ptype);
}

const std::vector<FaceSide> *Position::getSide()
{
    return &(this->vecSide);
}

std::ostream& operator<<(std::ostream& os, Position P){
    os << "Position: ptype = " << *P.getType();
    auto pvecSide = P.getSide();
    os << ", vecSide = { ";
    for(const auto& face : *pvecSide){
        os << face << " ";
    }
    os << "}";
    return os;
}
