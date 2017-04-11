/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "Position.h"
#include <iostream>

Position::Position():
    Position(F_UNDEFINED, F_UNDEFINED, F_UNDEFINED){
    std::cout << "No arguments passed..." << std::endl;
}

Position::Position(PositionType ptype):
    Position(F_UNDEFINED, F_UNDEFINED, F_UNDEFINED){
    setType(ptype);
}

Position::Position(FaceSide first):
    Position(first, F_UNDEFINED, F_UNDEFINED){
        //Noting for now
    }

Position::Position(FaceSide first, FaceSide second):
    Position(first, second, F_UNDEFINED){
        //Nothig for now
    }

Position::Position(FaceSide first, FaceSide second, FaceSide third):
    vecSide(SIZE, F_UNDEFINED){
    setSide(first, second, third);
}

PositionType *Position::getType()
{
    return &(this->ptype);
}

std::vector<FaceSide> *Position::getSide()
{
    return &(this->vecSide);
}

void Position::setSide(std::size_t pos, FaceSide face){
    if(pos < 0 || pos >= SIZE){
        std::cout << "pos: 0 <= pos < " << SIZE << "..." << std::endl;
        return;
    }
    vecSide[pos]=face;
}

void Position::setSide(FaceSide first){
    setSide(first, F_UNDEFINED, F_UNDEFINED);
}

void Position::setSide(FaceSide first, FaceSide second){
    setSide(first, second, F_UNDEFINED);
}

void Position::setSide(FaceSide first, FaceSide second, FaceSide third){
    if(anyOpposite(first, second, third))
        throw std::runtime_error(__func__ + std::string(": Contain opposite faces."));
    if(first != F_UNDEFINED)
    {
        vecSide[0]=first;
        setType(Center);
    }
    if(second != F_UNDEFINED)
    {
        vecSide[1]=second;
        setType(Edge);
    }
    if(third != F_UNDEFINED)
    {
        vecSide[2]=third;
        setType(Corner);
    }
}

void Position::setType(PositionType ptype){
    this->ptype = ptype;
}

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
/*
int main(int argc, char **argv)
{
    Position P = Position(Edge);
    PositionType *ptype = P.getType();
    std::cout << Center << std::endl;
    std::cout << argv[0] << std::endl;
    return 0;
}*/
