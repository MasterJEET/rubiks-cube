/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include <iostream>
#include "Facelet.h"

//Just for few testing

int main()
{
    Position pos(Front);
    Facelet F({Front,Left,Up});
    /*
    try{
    Position P = Position();
    P.setSide(Front, Up);
    P.setSide(Down);
    PositionType *ptype = P.getType();
    std::vector<FaceSide> *vecSide = P.getSide();
    std::cout << *ptype << std::endl;
    std::cout << vecSide->size() << std::endl;
    }
    catch(std::runtime_error& err){
        std::cout << err.what() << std::endl;
    }*/
    return 0;
}
