/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "gtest/gtest.h"
#include "cube.h"


const std::string CUBE_HOME = getHome();


int main(int argc, char **argv)
{

    Cubelet cr({red, right});
    Cubelet cr1a({front, red});
    cr1a *= front;
    cr *= up;
    std::cout << cr << std::endl;
    ( cr1a == cr );
    //testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
}

