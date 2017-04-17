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
    try{
    Position pos(Right,Up,Front);
    Facelet F = Facelet(pos);
    std::cout << *(F.getColor()) << std::endl;
    PositionType *pptype = F.getPositionType();
    std::cout << *pptype << std::endl;
    FaceSide *FS = F.getFaceSide();
    std::cout << *FS << std::endl;
    }
    catch(std::runtime_error& err){
        std::cout << err.what() << std::endl;
    }
    return 0;
}
