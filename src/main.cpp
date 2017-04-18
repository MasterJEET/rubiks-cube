/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 *
 * */

#include <iostream>
#include "Face.h"

//Just for few testing

int main()
{
    /*
    FaceSide d = Down;
    FaceSide l = Left;
    FaceSide f = Front;
    Facelet F(Red, d);
    Facelet F2(White, l);
    Facelet F3(Green, f);
    Position pos(d, f, l);
    Cubelet cub(pos,F,F2,F3);
    //auto fac = (*cub.getFacelet())[0];
    //std::cout << *fac.getColor() << std::endl;
    std::cout << cub << std::endl;
    Position pos2(l,d,f);
    cub.setPosition(&pos2);
    std::cout << cub << std::endl;
    */

    //Testcases for Face.h
    const FaceSide fac = Front;
    Face F = Face(fac);
    return 0;
}
