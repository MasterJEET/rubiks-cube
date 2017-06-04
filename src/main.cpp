/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include <iostream>
#include "Cubelet.h"
#include <Position.h>

//Just for few testing

int main(int argc, char **argv)
{
    //All facesides
    const FaceSide front = Front;
    const FaceSide back = Back;
    const FaceSide left = Left;
    const FaceSide right = Right;
    const FaceSide up = Up;
    const FaceSide down = Down;
    const FaceSide undefside = F_UNDEFINED;
    
    //std::cout << front << " " << back << " " << left << " " << right << " " << up << " " << down << " " << undefside << std::endl;
    
    //All colors
    const Color white = White;
    const Color yellow = Yellow;
    const Color orange = Orange;
    const Color red = Red;
    const Color green = Green;
    const Color blue = Blue;
    const Color undefcol = C_UNDEFINED;

    //std::cout << white << " " << yellow << " " << orange << " " << red << " " << green << " " << blue << " " << undefcol << std::endl;
    
    //All Position types
    const PositionType center = Center;
    const PositionType edge = Edge;
    const PositionType corner = Corner;
    const PositionType undefptype = P_UNDEFINED;
    
    //std::cout << center << " " << edge << " " << corner << " " << undefptype << std::endl;

    // ================================
    // ========= position test ========

    /*
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
   
    //Testing getSide() 
    const std::vector<const FaceSide *> * pvecSide;
    pvecSide = drf.getSide();
    std::cout << *(*pvecSide)[1] << std::endl;
    
    //Testing getPositionType()
    const PositionType * ptype;
    ptype = bl.getPositionType();
    std::cout << *ptype << std::endl;
    */
    // ======== positon ========

    // ============================    
    // ====== cubelet test ========
    
    try{

        //Center i.e. with one face
        Facelet fac1(&red, &right);
        //const Position r(&right);
        Cubelet cr(&fac1);
        const Position * const ppos = cr.getPosition();
        const PositionType * ptype1 = ppos->getPositionType();
        const std::vector<const FaceSide *> * pvecFac = ppos->getSide();
        const FaceSide *fac0 = (*pvecFac)[0];
        //const FaceSide fac10 = *fac0;
        //std::cout << *(*pvecFac)[0] << std::endl;
        //std::cout << *ptype1 << std::endl;
        //std::cout << *ppos << std::endl;
        //std::cout << cr << std::endl;
        /*
        //Edge i.e. with two faces
        Facelet fac2(&white, &front);
        Facelet fac3(&blue, &up);
        const Position fu(&front, &up);
        Cubelet cfu(&fu, &fac2, &fac3);
        std::cout << cfu << std::endl;

        //Corner i.e. with three faces
        Facelet fac4(&green, &back);
        Facelet fac5(&orange, &left);
        Facelet fac6(&white, &down);
        const Position bld(&back, &left, &down);
        Cubelet cbld(&bld, &fac4, &fac5, &fac6);
        std::cout << cbld << std::endl;

        //Testing getFacelet()
        std::cout << *(*cfu.getFacelet())[1]  << std::endl;

        //Testing getPosition()
        std::cout << *cbld.getPosition() << std::endl;

        //Testing setPosition()
        const Position frd(&front, &right, &down);
        cbld.setPosition(&frd);
        std::cout << *cbld.getPosition() << std::endl;
        */

    }
    catch(std::runtime_error& err){
        std::cout << err.what() << std::endl;
    }
    
    //======== cubelet ======== 
    return 0;
}
