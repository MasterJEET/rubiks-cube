/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "Position.h"
#include <iostream>

Position::Position()
{
    std::cout << "No arguments passed...Assuming PositionType: Center." << std::endl;
    //Position(Edge);
}

Position::Position(PositionType ptype)
{
    this->ptype = ptype;
}

Position::Position(Face first):
    Position(first, F_UNDEFINED, F_UNDEFINED){
        //Noting for now
    }

Position::Position(Face first, Face second):
    Position(first, second, F_UNDEFINED){
        //Nothig for now
    }

Position::Position(Face first, Face second, Face third)
{
    if(anyOpposite(first, second, third))
        throw std::runtime_error(__func__ + std::string(": Contain oppsite faces."));
    if(first != F_UNDEFINED)
    {
        vecFace.push_back(first);
        ptype = Center;
    }
    if(second != F_UNDEFINED)
    {
        vecFace.push_back(second);
        ptype = Edge;
    }
    if(third != F_UNDEFINED)
    {
        vecFace.push_back(third);
        ptype = Corner;
    }
}

PositionType *Position::getType()
{
    return &(this->ptype);
}

std::vector<Face> *Position::getFace()
{
    return &(this->vecFace);
}

bool Position::areOpposite(Face first, Face second)
{
    if((first == Front && second == Back) || (first == Back && second == Front))
        return true;
    if((first == Up && second == Down) || (first == Down && second == Up))
        return true;
    if((first == Left && second == Right) || (first == Right && second == Left))
        return true;
    return false;
}

bool Position::anyOpposite(Face first, Face second, Face third)
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
