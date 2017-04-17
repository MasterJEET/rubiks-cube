/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include <iostream>
#include "Facelet.h"
#include "Position.h"

//Just for few testing

int main()
{
    try{

        Facelet fac(White, Up);
        std::cout << fac << std::endl;
    }
    catch(std::runtime_error& err){
        std::cout << err.what() << std::endl;
    }
    return 0;
}
