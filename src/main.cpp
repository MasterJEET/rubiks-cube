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
    FaceSide f = Front;
    Facelet F(White, &f);
    f = Back;
    F.setFaceSide(&f);
    std::cout << *(F.getColor()) << std::endl;
    FaceSide *fac = F.getFaceSide();
    std::cout << *fac << std::endl;
    }
    catch(std::runtime_error& err){
        std::cout << err.what() << std::endl;
    }
    return 0;
}
