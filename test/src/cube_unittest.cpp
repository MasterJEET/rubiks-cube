/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 24th Jun 2017
 *
 * */

#include <fstream>
#include "cube.h"
#include "gtest/gtest.h"
#include "testcommon.h"

class CubeTest: public ::testing::Test {
    protected:
        Cube cube;
        Cube cube_f;
        std::ifstream is_cube;
        std::ifstream is_front;
        Position pf;
        Position pfd;
        Position pfur; 
        Position pd;
        Position pdl;
        Position pdfr;

        CubeTest(): pf(front), pfd(front, down), pfur(front, up, right),
                    pd(down), pdl(down, left), pdfr(down, front, right)
         {
            std::string filepath = std::string() + std::getenv("CUBE_HOME") + "/test/dat/cube.dat";
            is_cube.open( filepath  );
            if(!is_cube)
                throw std::runtime_error("Couldn't open file: \"" + filepath + "\"");
            else
                cube = Cube(is_cube);

            filepath = std::string() + std::getenv("CUBE_HOME") + "/test/dat/front.dat";
            is_front.open( filepath  );
            if(!is_front)
                throw std::runtime_error("Couldn't open file: \"" + filepath + "\"");
            else
                cube_f.createFace(is_front);
        }
};


/* ================== createFace =================
 * Cube() constructor uses Cube::createFace() function
 * read data from input stream and store into map.
 * createFace() is already run on 'cube_f' Cube object
 * Map map value will be checked here to confirm
 * createFace() worked fine
 *
 * 1. Cubelet::createFace(std::istream&)
 * 2. Cubelet::getFacelet(FaceSide);
 * 3. Cubelet::getFacelet(FaceSide, FaceSide);
 * 4. Cubelet::getFacelet(FaceSide, FaceSide, FaceSide);
 * 5. Cubelet::getFacelet(Position);
 * ===============================================
 */
TEST_F(CubeTest, face) {
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Front", cube_f.getFacelet(front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Front", cube_f.getFacelet(front, down));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Front", cube_f.getFacelet(front, up, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Front", cube_f.getFacelet(pf));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Front", cube_f.getFacelet(pfd));
    ASSERT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Front", cube_f.getFacelet(pfur));
}


/* ================ Initialization =================
 * Test for verifying Cube object is initialized as
 * expected. 
 * =================================================
 */
TEST_F(CubeTest, facelet) {

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Front", cube.getFacelet(front));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Front", cube.getFacelet(front, up));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Green, side = Front", cube.getFacelet(front, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Front", cube.getFacelet(front, down));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Orange, side = Front", cube.getFacelet(front, right));
    
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Green, side = Front", cube.getFacelet(front, up, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Front", cube.getFacelet(front, up, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Orange, side = Front", cube.getFacelet(front, down, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Front", cube.getFacelet(front, down, right));



    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Up", cube.getFacelet(up));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Up", cube.getFacelet(up, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Green, side = Up", cube.getFacelet(up, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Green, side = Up", cube.getFacelet(up, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Up", cube.getFacelet(up, right));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Green, side = Up", cube.getFacelet(up, back, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Yellow, side = Up", cube.getFacelet(up, back, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Up", cube.getFacelet(up, front, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Up", cube.getFacelet(up, front, right));


    
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Right", cube.getFacelet(right));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Right", cube.getFacelet(right, up));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Yellow, side = Right", cube.getFacelet(right, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Yellow, side = Right", cube.getFacelet(right, down));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Orange, side = Right", cube.getFacelet(right, back));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Yellow, side = Right", cube.getFacelet(right, up, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Orange, side = Right", cube.getFacelet(right, up, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Orange, side = Right", cube.getFacelet(right, down, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Yellow, side = Right", cube.getFacelet(right, down, back));



    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Orange, side = Left", cube.getFacelet(left));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Left", cube.getFacelet(left, up));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Yellow, side = Left", cube.getFacelet(left, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Left", cube.getFacelet(left, down));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Orange, side = Left", cube.getFacelet(left, front));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Yellow, side = Left", cube.getFacelet(left, up, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Left", cube.getFacelet(left, up, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Left", cube.getFacelet(left, down, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Green, side = Left", cube.getFacelet(left, down, front));



    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Yellow, side = Back", cube.getFacelet(back));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Orange, side = Back", cube.getFacelet(back, up));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Green, side = Back", cube.getFacelet(back, down));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Back", cube.getFacelet(back, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Back", cube.getFacelet(back, left));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Back", cube.getFacelet(back, up, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Orange, side = Back", cube.getFacelet(back, up, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Green, side = Back", cube.getFacelet(back, down, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Back", cube.getFacelet(back, down, left));



    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Green, side = Down", cube.getFacelet(down));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Down", cube.getFacelet(down, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Yellow, side = Down", cube.getFacelet(down, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Down", cube.getFacelet(down, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Down", cube.getFacelet(down, right));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Down", cube.getFacelet(down, front, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Blue, side = Down", cube.getFacelet(down, front, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = White, side = Down", cube.getFacelet(down, back, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Red, side = Down", cube.getFacelet(down, back, right));

}


TEST_F(CubeTest, cubelet){
    cube.getCubelet(Position(front));
    //EXPECT_PRED_FORMAT2(checkPrint, "Colors: { White } Position: ptype = Center, vecSide = { Front }", cube.getCubelet(front));
    //EXPECT_PRED_FORMAT2(checkPrint, "Colors: { Yellow } Position: ptype = Center, vecSide = { Back }", cube.getCubelet(back));
    //EXPECT_PRED_FORMAT2(checkPrint, "Colors: { Blue } Position: ptype = Center, vecSide = { Up }", cube.getCubelet(up));
    //EXPECT_PRED_FORMAT2(checkPrint, "Colors: { Red } Position: ptype = Center, vecSide = { Right }", cube.getCubelet(right));
    //EXPECT_PRED_FORMAT2(checkPrint, "Colors: { Orange } Position: ptype = Center, vecSide = { Left }", cube.getCubelet(left));
    //EXPECT_PRED_FORMAT2(checkPrint, "Colors: { Green } Position: ptype = Center, vecSide = { Down }", cube.getCubelet(down));
    //Facelet f1 = cube.getFacelet(front, down);
    //Facelet f2 = cube.getFacelet(down, front);
    //std::cout << f1 << std::endl;
    //std::cout << f2 << std::endl;
    //Cubelet c(&f1, &f2);
    //std::cout << c << std::endl;
    //Position pos(front, down);
    //Position pos2(down, front);
    //std::cout << cube.getCubelet(pos) << std::endl;
    //std::cout << cube.getCubelet(pos2) << std::endl;
}
