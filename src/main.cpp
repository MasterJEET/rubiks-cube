/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include <iostream>
#include "Position.h"

int main()
{
    try{
    Position P = Position(Right);
    //P.setSide(Up,Left,Back);
    PositionType *ptype = P.getType();
    std::cout << *ptype << std::endl;
    }
    catch(std::runtime_error& err){
        std::cout << err.what() << std::endl;
    }
    return 0;
}
