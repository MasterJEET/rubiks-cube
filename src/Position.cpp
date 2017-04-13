/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "Position.h"
#include <iostream>

Position::Position():ptype(P_UNDEFINED){
    std::cout << "No arguments passed..." << std::endl;
}

/*
Position::Position(PositionType ptype):
    ptype(ptype){
        //Nothing for now
}
*/

Position::Position(FaceSide first):
    vecSide{first}, ptype(Center){
        //Noting for now
    }

Position::Position(FaceSide first, FaceSide second):
    vecSide{first, second}, ptype(Edge){
        //Nothig for now
    }

Position::Position(FaceSide first, FaceSide second, FaceSide third):
    vecSide{first, second, third}, ptype(Corner){
        //Nothing for now
}

PositionType *Position::getType()
{
    return &(this->ptype);
}

std::vector<FaceSide> *Position::getSide()
{
    return &(this->vecSide);
}

FaceSide *Position::getFirstSide(){
    if(!vecSide.size()){
        std::cout << __func__ << ": FaceSides not yet assigned..." << std::endl;
        return NULL;
    }
    return &vecSide[0];
}

/*
 * Uncommenting won't work as logic is not completed, not required for this function
void Position::setSide(std::size_t pos, FaceSide face){
    if(pos < 0 || pos >= SIZE){
        std::cout << "pos: 0 <= pos < " << SIZE << "..." << std::endl;
        return;
    }
    vecSide[pos]=face;
}
*/

void Position::setSide(FaceSide first){
    setSide(first, F_UNDEFINED, F_UNDEFINED);
}

void Position::setSide(FaceSide first, FaceSide second){
    setSide(first, second, F_UNDEFINED);
}

void Position::setSide(FaceSide first, FaceSide second, FaceSide third){
    if(vecSide.size()){
        std::cout << "Faces are already set..." << std::endl;
        return;
    }
    if(anyOpposite(first, second, third))
        throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
    if(first != F_UNDEFINED)
    {
        vecSide.push_back(first);
        ptype = Center;
    }
    if(second != F_UNDEFINED)
    {
        vecSide.push_back(second);
        ptype = Edge;
    }
    if(third != F_UNDEFINED)
    {
        vecSide.push_back(third);
        ptype = Corner;
    }
}

/*
void Position::setType(PositionType ptype){
    this->ptype = ptype;
}
*/

bool Position::areOpposite(FaceSide first, FaceSide second)
{
    if((first == Front && second == Back) || (first == Back && second == Front))
        return true;
    if((first == Up && second == Down) || (first == Down && second == Up))
        return true;
    if((first == Left && second == Right) || (first == Right && second == Left))
        return true;
    return false;
}

bool Position::anyOpposite(FaceSide first, FaceSide second, FaceSide third)
{
    return (areOpposite(first, second) || areOpposite(first, third) || areOpposite(second, third));
}
