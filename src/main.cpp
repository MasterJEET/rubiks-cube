/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include <iostream> //Standard I/O
#include "gtest/gtest.h"
//#include <fstream>  //File stream I/O

//#include "Cube.h"

//Just for few testing

int main(int argc, char **argv)
{
//    //All facesides
//    const FaceSide front = Front;
//    const FaceSide back = Back;
//    const FaceSide left = Left;
//    const FaceSide right = Right;
//    const FaceSide up = Up;
//    const FaceSide down = Down;
//    const FaceSide undefside = F_UNDEFINED;
//    
//    //std::cout << front << " " << back << " " << left << " " << right << " " << up << " " << down << " " << undefside << std::endl;
//    
//    //All colors
//    const Color white = White;
//    const Color yellow = Yellow;
//    const Color orange = Orange;
//    const Color red = Red;
//    const Color green = Green;
//    const Color blue = Blue;
//    const Color undefcol = C_UNDEFINED;
//
//    //std::cout << white << " " << yellow << " " << orange << " " << red << " " << green << " " << blue << " " << undefcol << std::endl;
//    
//    //All Position types
//    const PositionType center = Center;
//    const PositionType edge = Edge;
//    const PositionType corner = Corner;
//    const PositionType undefptype = P_UNDEFINED;
//    
//    //std::cout << center << " " << edge << " " << corner << " " << undefptype << std::endl;
//
//    // ===============================
//    // ========= COMMON TEST =========
//    /*
//    //Printing Color
//    std::cout << blue << std::endl;
//    //Printing FaceSide
//    std::cout << undefside << std::endl;
//    //Printing PositionType
//    std::cout << corner << std::endl;
//
//    //Checking oppsite face
//    std::cout << areOpposite(front, back) << std::endl;
//    std::cout << areOpposite(front, down) << std::endl;
//    std::cout << anyOpposite(front, down, back) << std::endl;
//    std::cout << anyOpposite(front, down, right) << std::endl;
//
//    //Getting Color from string constant
//    std::cout << ColorFromStr("W") << std::endl;
//
//    //Getting FaceSide from string constant
//    std::cout << FaceSideFromStr("L") << std::endl;
//    
//    //Printing All Colors
//    printAllColor();
//
//    //Printing All FaceSides
//    printAllFaceSide();
//
//    // =========== COMMON ============
//    */
//
//    // ==============================
//    // ======== FACELET TEST ========
//    /*
//    // Testing constructor, Color as first argument
//    Facelet flet(red, left);
//    std::cout << "Color first, " << flet << std::endl;
//
//    // Testing constructor, FaceSide as first argument
//    Facelet flr(left, red);
//    std::cout << "FaceSide first, " << flr << std::endl;
//    
//    // Testing getColor()
//    std::cout << flet.getColor() << std::endl;
//
//    // Testing getFaceSide()
//    std::cout << flet.getFaceSide() << std::endl;
//    
//    // Testing setFaceSide()
//    flet.setFaceSide(down);
//    std::cout << flet << std::endl;
//    */
//    // =========== FACELET ==========
//
//
//    // ================================
//    // ========= position test ========
//
//    /*
//    //front center
//    Position f(front);
//    std::cout << f << std::endl;
//    
//    //back left edge
//    Position bl(back, left);
//    std::cout << bl  << std::endl;
//
//    //down right front corner
//    Position drf(down, right, front);
//    std::cout << drf << std::endl;
//
//    //right left, opposite face error
//    //Position rl(&right, &left);
//    
//    //down, front and back, opposite face error
//    //Position dfb(&down, &front, &back);
//   
//    //Testing getSide() 
//    const std::vector<FaceSide> *pvecSide;
//    pvecSide = drf.getSide();
//    std::cout << (*pvecSide)[1] << std::endl;
//    
//    //Testing getPositionType()
//    std::cout << bl.getPositionType() << std::endl;
//    
//    //Testing getSideAt()
//    std::cout << drf.getSideAt(2) << std::endl;
//    */
//    // ======== positon ========
//
//    // ============================    
//    // ====== cubelet test ========
//    /*
//    try{
//
//        //Center i.e. with one face
//        Facelet fac1(red, right);
//        Cubelet cr(fac1);
//        std::cout << cr << std::endl;
//        
//        //Edge i.e. with two faces
//        Facelet fac2(white, front);
//        Facelet fac3(blue, up);
//        Cubelet cfu(fac2, fac3);
//        std::cout << cfu << std::endl;
//        
//        //Corner i.e. with three faces
//        Facelet fac4(green, back);
//        Facelet fac5(orange, left);
//        Facelet fac6(white, down);
//        Cubelet cbld(fac4, fac5, fac6);
//        std::cout << cbld << std::endl;
//        
//        //Testing getFacelet()
//        std::cout << (cfu.getFacelet())->at(0) << std::endl;
//        
//        //Testing getFaceletAt()
//        std::cout << *cr.getFaceletAt(0) << std::endl;
//        
//        //Testing getPosition()
//        std::cout << cbld.getPosition() << std::endl;
//        
//        //Testing setPosition()
//        const Position frd(front, right, down);
//        cbld.setPosition(frd);
//        std::cout << cbld.getPosition() << std::endl;
//
//    }
//    catch(std::runtime_error& err){
//        std::cout << err.what() << std::endl;
//    }
//    */
//    //======== cubelet ======== 
//
//    
//    // ====================================
//    // ============ CUBE TEST =============
//    
//    //Default condtructor
//    Cube cube;
//    
//    std::ifstream ifs;
//    std::string strCUBE_HOME = std::getenv("CUBE_HOME");
//    
//    ifs.open(strCUBE_HOME +  "/dat/front.dat");
//    if(!ifs)
//        std::cout << "file NOT open" << std::endl;
//    else
//        cube = Cube(ifs);
//    
//    const Facelet& flet = cube.getFacelet(Front, F_UNDEFINED, F_UNDEFINED);
//    std::cout << flet << std::endl;
//
//    // ============= CUBE =================
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
