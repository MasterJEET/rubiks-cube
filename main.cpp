/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "gtest/gtest.h"
#include "cube.h"
#include <fstream>


const std::string CUBE_HOME = getHome();


int main(int argc, char **argv)
{

    Facelet frr(red, right);
    Cubelet c1(frr);
    Cubelet c2(frr);
    c1 == c2;
    //testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
}

