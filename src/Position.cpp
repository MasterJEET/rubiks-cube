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
    Position(Center);
}

Position::Position(PositionType ptype)
{
    this->ptype = ptype;
}

PositionType *Position::getType()
{
    return &(this->ptype);
}

int main(int argc, char **argv)
{
    Position P = Position(Edge);
    PositionType *ptype = P.getType();
    std::cout << Center << std::endl;
    std::cout << argv[0] << std::endl;
    return 0;
}
