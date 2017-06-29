/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "gtest/gtest.h"
#include "cube.h"

int main(int argc, char **argv)
{
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
