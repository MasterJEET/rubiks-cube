/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "gtest/gtest.h"

int main(int argc, char **argv)
{
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
