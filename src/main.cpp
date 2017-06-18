/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "gtest/gtest.h"

int main(int argc, char **argv)
{
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
