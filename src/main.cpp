/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include <iostream>
//#include "Cubelet.h"
#include <Position.h>
//#include "Facelet.h"
//#include "Position.h"
//#include "common.h"

//Just for few testing

int main(int argc, char **argv)
{
    // ====== cubelet test ========
    /*
    try{
        FaceSide up = Up;
        FaceSide right = Right;
        Facelet fac1(White, &up);
        Facelet fac2(Orange, &right);
        std::cout << fac1 << std::endl;
        std::cout << fac2 << std::endl;
        Position ur(&up, &right);
        Cubelet cur(ur, &fac1, &fac2);
        std::cout << cur << std::endl;
        FaceSide fs = Up;
        Facelet fac(White, fs);
        std::cout << fac << std::endl;
    }
    catch(std::runtime_error& err){
        std::cout << err.what() << std::endl;
    }
    ======== cubelet ======== */
    /*
    
    // ================================
    // ========= position test ========

    const FaceSide front = Front;
    const FaceSide back = Back;
    const FaceSide left = Left;
    const FaceSide right = Right;
    const FaceSide up = Up;
    const FaceSide down = Down;
    const FaceSide undef = F_UNDEFINED;
    std::cout << front << " " << back << " " << left << " " << right << " " << up << " " << down << " " << undef << std::endl;
    
    //front center
    Position f(&front);
    std::cout << f << std::endl;
    
    //back left edge
    Position bl(&back, &left);
    std::cout << bl  << std::endl;

    //down right front corner
    Position drf(&down, &right, &front);
    std::cout << drf << std::endl;

    //right left, opposite face error
    //Position rl(&right, &left);
    
    //down, front and back, opposite face error
    //Position dfb(&down, &front, &back);
    */
    // ======== positon ========
    
    return 0;
}
