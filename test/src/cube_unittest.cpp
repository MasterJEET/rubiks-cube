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
        FaceletPosition pf;
        FaceletPosition pfd;
        FaceletPosition pfur; 
        Position pd;
        Position pdl;
        Position pdfr;

        CubeTest(): pf(front), pfd(front, down), pfur(front, up, right),
                    pd(down), pdl(down, left), pdfr(down, front, right)
         {
            std::string filepath = std::string() + CUBE_HOME + "/test/dat/cube.dat";
            is_cube.open( filepath  );
            if(!is_cube)
                throw std::runtime_error("Couldn't open file: \"" + filepath + "\"");
            else
                cube = Cube(is_cube);

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
    //Checking Cubelets with only one Facelet( Center of each Face )
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Front, White) }", cube.getCubelet(front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Back, Yellow) }", cube.getCubelet(back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Up, Blue) }", cube.getCubelet(up));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Right, Red) }", cube.getCubelet(right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Left, Orange) }", cube.getCubelet(left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Down, Green) }", cube.getCubelet(down));

    ////Cubelets with double Facelets ( Edge )
    //Vector of vector of pair FaceSides
    typedef std::vector< std::vector<FaceSide> > vFS;
    vFS vdfs = { 
                                        { front, up }, { front, right }, { front, down }, { front, left },
                                        { up, right }, { down, right }, { down, left }, { up, left },
                                        { back, up }, { back, right }, { back, down }, { back, left }
                                      };
    //Vector of vector of poir Colors
    typedef std::vector< std::vector<Color> > vCol;
    vCol vdc = {
                                        { red, green }, { orange, yellow }, { blue, white  }, { green, orange  },
                                        { red, white }, { blue, yellow }, { red, blue }, { green, white },
                                        { orange, white}, { blue, orange }, { green, yellow }, { red, yellow } 
                                      };

    {
    vFS::iterator vf;
    vCol::iterator vc;

    for( vc = vdc.begin(), vf = vdfs.begin(); vc != vdc.end()  ; vf++, vc++ ){
        FaceletPosition fp1( vf->at(0), vf->at(1) );   FaceletPosition fp2( vf->at(1), vf->at(0) );
        Facelet f1(fp1, vc->at(0) );   Facelet f2(fp2, vc->at(1) );
        EXPECT_EQ( Cubelet( f1, f2), cube.getCubelet( fp1 ) );
    }
    }

    ////Cubelets with triple Facelets ( Corner )
    //Vector of vector of triple FaceSides
    vFS vtfs = {
        { front, right, up}, { back, right, up }, { back, left, up}, { front, left, up },
        { front, right, down}, { back, right, down }, { back, left, down}, { front, left, down }
    };

    vCol vtc = {
        { red, yellow, blue }, { blue, orange, yellow }, { orange, yellow, green }, { green, white, red },
        { white, orange, blue }, { green, yellow, red }, { blue, red, white }, { orange, green, white }
    };

    {
    vFS::iterator vf;
    vCol::iterator vc;

    for( vc = vtc.begin(), vf = vtfs.begin(); vc != vtc.end()  ; vf++, vc++ ){
        FaceletPosition fp1( vf->at(0), vf->at(1), vf->at(2) );   FaceletPosition fp2( vf->at(1), vf->at(0), vf->at(2) );   FaceletPosition fp3( vf->at(2), vf->at(0), vf->at(1) );
        Facelet f1(fp1, vc->at(0) );   Facelet f2(fp2, vc->at(1) );   Facelet f3(fp3, vc->at(2) );
        EXPECT_EQ( Cubelet( f1, f2, f3), cube.getCubelet( fp1 ) );
    }
    }
    

}

