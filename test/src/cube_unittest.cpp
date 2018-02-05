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
#include "cuception.h"

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
            std::string linearpath = std::string() + CUBE_HOME + "/test/dat/cube_linear.dat";
            is_cube.open( linearpath  );
            if(!is_cube)
                throw std::runtime_error("Couldn't open file: \"" + linearpath + "\"");
            else
                cube = Cube(is_cube);


        }
};


/* ================== createFace =================
 * Cube() constructor uses Cube::createFaceFromStepInput() function
 * read data from input stream and store into array.
 * createFaceFromStepInput() is already run on 'cube_f' Cube object.
 * Array value will be checked here to confirm
 * createFaceFromStepInput() worked fine
 *
 * 1. Cubelet::createFaceFromStepInput(std::istream&)
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

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = W, side = Front", cube.getFacelet(front));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = R, side = Front", cube.getFacelet(front, up));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = G, side = Front", cube.getFacelet(front, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = B, side = Front", cube.getFacelet(front, down));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = O, side = Front", cube.getFacelet(front, right));
    
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = G, side = Front", cube.getFacelet(front, up, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = R, side = Front", cube.getFacelet(front, up, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = O, side = Front", cube.getFacelet(front, down, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = W, side = Front", cube.getFacelet(front, down, right));



    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = B, side = Up", cube.getFacelet(up));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = W, side = Up", cube.getFacelet(up, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = G, side = Up", cube.getFacelet(up, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = G, side = Up", cube.getFacelet(up, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = R, side = Up", cube.getFacelet(up, right));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = G, side = Up", cube.getFacelet(up, back, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Y, side = Up", cube.getFacelet(up, back, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = R, side = Up", cube.getFacelet(up, front, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = B, side = Up", cube.getFacelet(up, front, right));


    
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = R, side = Right", cube.getFacelet(right));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = W, side = Right", cube.getFacelet(right, up));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Y, side = Right", cube.getFacelet(right, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Y, side = Right", cube.getFacelet(right, down));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = O, side = Right", cube.getFacelet(right, back));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Y, side = Right", cube.getFacelet(right, up, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = O, side = Right", cube.getFacelet(right, up, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = O, side = Right", cube.getFacelet(right, down, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Y, side = Right", cube.getFacelet(right, down, back));



    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = O, side = Left", cube.getFacelet(left));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = W, side = Left", cube.getFacelet(left, up));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Y, side = Left", cube.getFacelet(left, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = B, side = Left", cube.getFacelet(left, down));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = O, side = Left", cube.getFacelet(left, front));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Y, side = Left", cube.getFacelet(left, up, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = W, side = Left", cube.getFacelet(left, up, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = R, side = Left", cube.getFacelet(left, down, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = G, side = Left", cube.getFacelet(left, down, front));



    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Y, side = Back", cube.getFacelet(back));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = O, side = Back", cube.getFacelet(back, up));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = G, side = Back", cube.getFacelet(back, down));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = B, side = Back", cube.getFacelet(back, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = R, side = Back", cube.getFacelet(back, left));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = B, side = Back", cube.getFacelet(back, up, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = O, side = Back", cube.getFacelet(back, up, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = G, side = Back", cube.getFacelet(back, down, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = B, side = Back", cube.getFacelet(back, down, left));



    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = G, side = Down", cube.getFacelet(down));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = W, side = Down", cube.getFacelet(down, front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = Y, side = Down", cube.getFacelet(down, back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = R, side = Down", cube.getFacelet(down, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = B, side = Down", cube.getFacelet(down, right));

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = W, side = Down", cube.getFacelet(down, front, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = B, side = Down", cube.getFacelet(down, front, right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = W, side = Down", cube.getFacelet(down, back, left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet: col = R, side = Down", cube.getFacelet(down, back, right));

}



TEST_F(CubeTest, cubelet){
    ///Checking Cubelets with only one Facelet( Center of each Face )
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Front, W) }", cube.getCubelet(front));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Back, Y) }", cube.getCubelet(back));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Up, B) }", cube.getCubelet(up));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Right, R) }", cube.getCubelet(right));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Left, O) }", cube.getCubelet(left));
    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Down, G) }", cube.getCubelet(down));

    //////Cubelets with double Facelets ( Edge )
    ///Vector of vector of pair FaceSides
    typedef std::vector< std::vector<FaceSide> > vFS;
    vFS vdfs = { 
                                        { front, up }, { front, right }, { front, down }, { front, left },
                                        { up, right }, { down, right }, { down, left }, { up, left },
                                        { back, up }, { back, right }, { back, down }, { back, left }
                                      };
    ///Vector of vector of poir Colors
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

    //////Cubelets with triple Facelets ( Corner )
    ///Vector of vector of triple FaceSides
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
        FaceletPosition fp1( vf->at(0), vf->at(1), vf->at(2) );
        FaceletPosition fp2( vf->at(1), vf->at(0), vf->at(2) );
        FaceletPosition fp3( vf->at(2), vf->at(0), vf->at(1) );
        Facelet f1(fp1, vc->at(0) );
        Facelet f2(fp2, vc->at(1) );
        Facelet f3(fp3, vc->at(2) );
        EXPECT_EQ( Cubelet( f1, f2, f3), cube.getCubelet( fp1 ) );
    }
    }
    

}


//TEST_F(CubeTest, show){
//    cube.show(front);
//    cube.show(back);
//    cube.show(left);
//    cube.show(right);
//    cube.show(up);
//    cube.show(down);
//}

//TEST_F(CubeTest, getSideOfColor){
//    Color cUp       = cube.getFacelet(up).getColor();
//    Color cRight    = cube.getFacelet(right).getColor();
//    Color cDown     = cube.getFacelet(down).getColor();
//    Color cLeft     = cube.getFacelet(left).getColor();
//    Color cFront    = cube.getFacelet(front).getColor();
//    Color cBack     = cube.getFacelet(back).getColor();
//
//    cube.rotate(front);
//
//    EXPECT_EQ(cube.getSideOfColor(cUp),     right);
//    EXPECT_EQ(cube.getSideOfColor(cRight),  down);
//    EXPECT_EQ(cube.getSideOfColor(cDown),   left);
//    EXPECT_EQ(cube.getSideOfColor(cLeft),   up);
//    EXPECT_EQ(cube.getSideOfColor(cFront),  front);
//    EXPECT_EQ(cube.getSideOfColor(cBack),   back);
//
//    cube.rotateMid(front,3);
//
//    EXPECT_EQ(cube.getSideOfColor(cUp),     up);
//    EXPECT_EQ(cube.getSideOfColor(cRight),  right);
//    EXPECT_EQ(cube.getSideOfColor(cDown),   down);
//    EXPECT_EQ(cube.getSideOfColor(cLeft),   left);
//    EXPECT_EQ(cube.getSideOfColor(cFront),  front);
//    EXPECT_EQ(cube.getSideOfColor(cBack),   back);
//
//}


//TEST_F(CubeTest, setEquivalentColor){
//    Color cf = green;
//    Color cu, cr, cd, cl;
//    cube.setEquivalentColor(cf, cu, cr, cd, cl);
//
//    FaceSide f = cube.getSideOfColor(cf);
//    FaceSide u,r,d,l;
//    setEquivalentFaceSide(f,u,r,d,l);
//
//    EXPECT_EQ(cu,   cube.getFacelet(u).getColor());
//    EXPECT_EQ(cr,   cube.getFacelet(r).getColor());
//    EXPECT_EQ(cd,   cube.getFacelet(d).getColor());
//    EXPECT_EQ(cl,   cube.getFacelet(l).getColor());
//}


TEST_F(CubeTest, rotateSide){
    Cube cube_old(cube);
    cube.rotateSide(back);
    
    EXPECT_EQ(cube_old.getCubelet(back), cube.getCubelet(back));
    
    EXPECT_EQ(cube_old.getCubelet({up,back})*back, cube.getCubelet({back,left}));
    EXPECT_EQ(cube_old.getCubelet({right,back})*back, cube.getCubelet({back,up}));
    EXPECT_EQ(cube_old.getCubelet({down,back})*back, cube.getCubelet({back,right}));
    EXPECT_EQ(cube_old.getCubelet({left,back})*back, cube.getCubelet({back,down}));
    
    EXPECT_EQ(cube_old.getCubelet({up,back,right})*back, cube.getCubelet({up,back,left}));
    EXPECT_EQ(cube_old.getCubelet({up,back,left})*back, cube.getCubelet({down,back,left}));
    EXPECT_EQ(cube_old.getCubelet({down,back,left})*back, cube.getCubelet({down,back,right}));
    EXPECT_EQ(cube_old.getCubelet({down,back,right})*back, cube.getCubelet({up,back,right}));
    
    
    Cube cube_new(cube_old);
    cube_new.rotateSide(left,false);    //set is_clockwise flag to false, face will be rotated anti-clockwise
    
    EXPECT_EQ(cube_old.getCubelet(left), cube_new.getCubelet(left));
    
    EXPECT_EQ(cube_old.getCubelet({up,left})*right, cube_new.getCubelet({back,left}));
    EXPECT_EQ(cube_old.getCubelet({back,left})*right, cube_new.getCubelet({down,left}));
    EXPECT_EQ(cube_old.getCubelet({down,left})*right, cube_new.getCubelet({front,left}));
    EXPECT_EQ(cube_old.getCubelet({front,left})*right, cube_new.getCubelet({up,left}));
    
    EXPECT_EQ(cube_old.getCubelet({up,back,left})*right, cube_new.getCubelet({down,back,left}));
    EXPECT_EQ(cube_old.getCubelet({down,back,left})*right, cube_new.getCubelet({down,front,left}));
    EXPECT_EQ(cube_old.getCubelet({down,front,left})*right, cube_new.getCubelet({up,front,left}));
    EXPECT_EQ(cube_old.getCubelet({up,front,left})*right, cube_new.getCubelet({up,back,left}));
}


TEST_F(CubeTest,rotateMid){

    Cube cube_old(cube);
    cube.rotateMid(down);
    
    EXPECT_EQ(cube_old.getCubelet(front)*down, cube.getCubelet(right));
    EXPECT_EQ(cube_old.getCubelet(right)*down, cube.getCubelet(back));
    EXPECT_EQ(cube_old.getCubelet(back)*down, cube.getCubelet(left));
    EXPECT_EQ(cube_old.getCubelet(left)*down, cube.getCubelet(front));
    
    EXPECT_EQ(cube_old.getCubelet({front,right})*down, cube.getCubelet({back,right}));
    EXPECT_EQ(cube_old.getCubelet({back,right})*down, cube.getCubelet({back,left}));
    EXPECT_EQ(cube_old.getCubelet({back,left})*down, cube.getCubelet({front,left}));
    EXPECT_EQ(cube_old.getCubelet({front,left})*down, cube.getCubelet({front,right}));


    Cube cube_new(cube_old);
    cube_new.rotateMid(right,false);    //set is_clockwise flag to false, layer will be rotated anti-clockwise

    EXPECT_EQ(cube_old.getCubelet(front)*left, cube_new.getCubelet(down));
    EXPECT_EQ(cube_old.getCubelet(down)*left, cube_new.getCubelet(back));
    EXPECT_EQ(cube_old.getCubelet(back)*left, cube_new.getCubelet(up));
    EXPECT_EQ(cube_old.getCubelet(up)*left, cube_new.getCubelet(front));

    EXPECT_EQ(cube_old.getCubelet({up,front})*left, cube_new.getCubelet({down,front}));
    EXPECT_EQ(cube_old.getCubelet({down,front})*left, cube_new.getCubelet({down,back}));
    EXPECT_EQ(cube_old.getCubelet({down,back})*left, cube_new.getCubelet({up,back}));
    EXPECT_EQ(cube_old.getCubelet({up,back})*left, cube_new.getCubelet({up,front}));

}


TEST_F(CubeTest,rotate){

    Cube cube_old(cube);
    cube.rotate(up);

    EXPECT_EQ(cube_old.getCubelet(front)*up, cube.getCubelet(left));
    EXPECT_EQ(cube_old.getCubelet(back,left)*up, cube.getCubelet(back,right));
    EXPECT_EQ(cube_old.getCubelet(down,right)*up, cube.getCubelet(down,front));
    EXPECT_EQ(cube_old.getCubelet(down,left,front)*up, cube.getCubelet(down,left,back));

    Cube cube_new(cube_old);
    cube_new.rotate(front,false);

    EXPECT_EQ(cube_old.getCubelet(down)*back, cube_new.getCubelet(right));
    EXPECT_EQ(cube_old.getCubelet(up,left)*back, cube_new.getCubelet(down,left));
    EXPECT_EQ(cube_old.getCubelet(down,back)*back, cube_new.getCubelet(back,right));
    EXPECT_EQ(cube_old.getCubelet(right,up,front)*back, cube_new.getCubelet(up,left,front));


    cube_new = cube_old;
    cube_new.rotate(right,2,true);
    EXPECT_EQ((cube_old.getFacelet(right,back)*left)*left, cube_new.getFacelet(right,front));
    EXPECT_EQ(cube_old.getFacelet(left), cube_new.getFacelet(left));
    EXPECT_EQ((cube_old.getFacelet(front,left,down)*left)*left, cube_new.getFacelet(back,up,left));

    cube_new = cube_old;
    cube_new.rotate(down,false,7);
    EXPECT_EQ(cube_old.getFacelet(back,up,right)*down, cube_new.getFacelet(left,back,up));
}


TEST_F(CubeTest, opposite_color){
    EXPECT_TRUE(cube.areOppColor(white, yellow));
    EXPECT_FALSE(cube.areOppColor(white, red));

    EXPECT_TRUE(cube.anyOppColor(yellow, orange, red));
    EXPECT_FALSE(cube.anyOppColor(green, red, yellow));

    EXPECT_TRUE(cube.anyOppColor(blue, green, white));
    EXPECT_FALSE(cube.anyOppColor(white, blue, orange));
}


TEST_F(CubeTest, ColorSetToInt){
    std::size_t tR = cube.ColorSetToInt(red);
    std::size_t tB = cube.ColorSetToInt(blue);
    
    EXPECT_EQ(tR, 3);
    cube.rotateMid();
    EXPECT_EQ(tB, 5);


    std::size_t tWR = cube.ColorSetToInt(white, red);
    std::size_t tRW = cube.ColorSetToInt(red, white);
    std::size_t tRB = cube.ColorSetToInt(red, blue);
    std::size_t tBR = cube.ColorSetToInt(blue, red);
    std::size_t tWO = cube.ColorSetToInt(white, orange);

    cube.rotate(up);
    EXPECT_EQ(tWR, tRW);
    EXPECT_EQ(tBR, tRB);
    EXPECT_EQ(tBR, 17); cube.rotateSide(down);
    EXPECT_EQ(tWO, 6);
    EXPECT_THROW(cube.ColorSetToInt(white, white), std::runtime_error);
    EXPECT_THROW(cube.ColorSetToInt(white, yellow), std::runtime_error);


    ColorSet cWOB( white, orange, blue );
    std::size_t tWOB = cube.ColorSetToInt(cWOB);
    std::size_t tOBW = cube.ColorSetToInt(orange, blue, white);
    std::size_t tBWO = cube.ColorSetToInt(blue, white, orange);
    std::size_t tYRB = cube.ColorSetToInt(yellow, red, blue);
    std::size_t tWOG = cube.ColorSetToInt(white, orange, green);


    cube.rotate(back);
    EXPECT_EQ(tWOB, tOBW);
    EXPECT_EQ(tWOB, tBWO);
    EXPECT_EQ(tYRB, 25);    cube.rotateMid(left);
    EXPECT_EQ(tWOG, 18);
    EXPECT_THROW(cube.ColorSetToInt(white, red, red), std::runtime_error);  //same Color
    EXPECT_THROW(cube.ColorSetToInt(green, red, orange), std::runtime_error);  //opposite Color

    CubeletPosition cp(up, back, left);
    vecFacelet vFac = cube.getCubelet(cp).getFacelet();
    Color c1 = vFac[0].getColor();
    Color c2 = vFac[1].getColor();
    Color c3 = vFac[2].getColor();
    ColorSet cs1(c1, c2, c3);
    
    EXPECT_EQ( cube.ColorSetToInt(cs1), cube.ColorSetToInt(cp) );


    CubeletPosition cp2(front);
    vecFacelet vFac2 = cube.getCubelet(cp2).getFacelet();
    Color c4 = vFac2[0].getColor();
    ColorSet cs2(c4);

    EXPECT_EQ( cube.ColorSetToInt(cs2), cube.ColorSetToInt(cp2) );
}


TEST_F(CubeTest, getCubeletUsingColorSet){
    Cubelet c1b( cube.getCubelet(red,yellow) );
    cube.rotate(left);
    Cubelet c1a( cube.getCubelet(yellow,red) );

    EXPECT_EQ( c1a, c1b * left );
    

    Cubelet c2b = cube.getCubelet( white );
    cube.rotate( down, 2 );
    Cubelet c2a = cube.getCubelet( white );
    c2a *= up; c2b *= down;

    EXPECT_EQ( c2a, c2b );


    Cubelet c3b( cube.getCubelet(yellow, orange, blue) );
    cube.rotate( back, false );
    Cubelet c3a( cube.getCubelet(blue, yellow, orange) );

    EXPECT_EQ( c3b * front, c3a );

}


TEST(colorset, constructor){
    ColorSet cs1(red, white, blue);
    EXPECT_TRUE(cs1.min() <= cs1.mid());
    EXPECT_TRUE(cs1.mid() <= cs1.max());

    ColorSet cs2(yellow, green, orange);
    EXPECT_TRUE(cs2.min() <= cs2.mid());
    EXPECT_TRUE(cs2.mid() <= cs2.max());

    ColorSet cs3(yellow, red);
    EXPECT_TRUE(cs3.min() <= cs3.mid());
    EXPECT_TRUE(cs3.mid() <= cs3.max());

    ColorSet cs4(green);
    EXPECT_TRUE(cs4.min() <= cs4.mid());
    EXPECT_TRUE(cs4.mid() <= cs4.max());

    //same Color
    EXPECT_THROW( ColorSet cs5(red, red), std::runtime_error );
    //Opposite Color
    EXPECT_THROW( ColorSet cs5(white, green, white), std::runtime_error );

    std::vector<Color> vCol1;
    EXPECT_THROW( ColorSet cs6(vCol1), std::runtime_error );    //Empty vector
    vCol1.push_back(yellow);
    vCol1.push_back(orange);
    vCol1.push_back(blue);

    ColorSet cs7(vCol1);
    EXPECT_TRUE(cs7.min() <= cs7.mid());
    EXPECT_TRUE(cs7.mid() <= cs7.max());

    vCol1.push_back( green );
    EXPECT_THROW( ColorSet cs8(vCol1), std::runtime_error );    //Size > 3


}


TEST(Cube, Cube){
    Cube C;

    for(const auto& f:{front,back,up,down,right,back})
    {
        Color col = C.getFacelet(f).getColor();
        for(const auto& fp: getEquivalentFletPos(f))
        {
            EXPECT_EQ(col, C.getFacelet(fp).getColor());
        }
    }
}

TEST(Cube, getCubeletPosition){

    //Out of range
    EXPECT_THROW(Cube::getCubeletPosition(30), std::out_of_range);

    //Center Positions
    EXPECT_EQ(Cube::getCubeletPosition(2), CubeletPosition(up));
    EXPECT_EQ(Cube::getCubeletPosition(5), CubeletPosition(right));

    //Edge Positions
    EXPECT_EQ(Cube::getCubeletPosition(8), CubeletPosition(left, front));
    EXPECT_EQ(Cube::getCubeletPosition(11), CubeletPosition(back, down));
    EXPECT_EQ(Cube::getCubeletPosition(16), CubeletPosition(left, down));

    //Corener Postions
    EXPECT_EQ(Cube::getCubeletPosition(21), CubeletPosition(front, right, down));
    EXPECT_EQ(Cube::getCubeletPosition(23), CubeletPosition(up, right, back));


}

TEST(Cube, getFaceletPosition){
    //Out of range
    EXPECT_THROW(Cube::getFaceletPosition(54), std::out_of_range);

    //Center Positions
    EXPECT_EQ(Cube::getFaceletPosition(45), FaceletPosition(right));

    //Edge Positions
    EXPECT_EQ(Cube::getFaceletPosition(22), FaceletPosition(up, left));
    EXPECT_EQ(Cube::getFaceletPosition(12), FaceletPosition(back, down));
    EXPECT_EQ(Cube::getFaceletPosition(47), FaceletPosition(right, back));
    EXPECT_EQ(Cube::getFaceletPosition(28), FaceletPosition(down, front));

    //Corner Positions
    EXPECT_EQ(Cube::getFaceletPosition(41), FaceletPosition(left,up,front));
    EXPECT_EQ(Cube::getFaceletPosition(17), FaceletPosition(back,up,right));
    EXPECT_EQ(Cube::getFaceletPosition(32), FaceletPosition(down,front,right));
    EXPECT_EQ(Cube::getFaceletPosition(43), FaceletPosition(left,down,back));

}

TEST(Cube, getColorFromInt){
    //Out of range
    EXPECT_THROW(Cube::getColorFromInt(6), std::out_of_range);

    EXPECT_EQ(Cube::getColorFromInt(1), yellow);
    EXPECT_EQ(Cube::getColorFromInt(4), green);
}

TEST(Cube, CubePath){
    EXPECT_THROW(Cube C1("/home/masterjeet/cube.dat"), std::runtime_error);
}

//check for duplicate entries in 
TEST(input, duplicate){
    std::string errorpath = std::string() + CUBE_HOME + "/test/dat/cube_duplicate.dat";

    EXPECT_THROW(Cube C(errorpath), NumOfFaceletException);
}

//Checking count of Facelets with given Color
TEST(input, count){
    std::ifstream is_cube_color;
    std::string errorpath = std::string() + CUBE_HOME + "/test/dat/cube_col.dat";
    is_cube_color.open( errorpath );

    EXPECT_THROW(Cube C(is_cube_color), NumOfColorException);
}

//Checking no edge Cubelet has same Color
TEST(input, edgesame){
    std::ifstream is_cube;
    std::string errorpath = std::string() + CUBE_HOME + "/test/dat/cube_edge.dat";
    is_cube.open( errorpath );

    EXPECT_THROW( Cube C(is_cube), EdgeColorException);
}

//Checking no edge Cubelet has opposite Color
TEST(input, edgeopp){
    std::ifstream is_cube;
    std::string errorpath = std::string() + CUBE_HOME + "/test/dat/cube_opp.dat";
    is_cube.open( errorpath );

    EXPECT_THROW( Cube C(is_cube), EdgeColorException);
}

//Checking Colors on a given corner Cubelet are different
TEST(input, cornersame){
    std::ifstream is_cube;
    std::string errorpath = std::string() + CUBE_HOME + "/test/dat/cube_corner_same.dat";
    is_cube.open( errorpath );

    EXPECT_THROW(Cube C(is_cube), CornerColorException);
}

//Checking given corner Cubelet doesn't contain opposite Color
TEST(input, corneropp){
    std::ifstream is_cube;
    std::string errorpath = std::string() + CUBE_HOME + "/test/dat/cube_corner_opp.dat";
    is_cube.open( errorpath );

    EXPECT_THROW(Cube C(is_cube), CornerColorException);
}


TEST(Equivalence,Edge){
    FaceSide f;
    CubeletPosition pu,pr,pd,pl;

    f = front;
    vecCletPos v = vecEdgeEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,front), pu);
    EXPECT_EQ(CubeletPosition(right,front), pr);
    EXPECT_EQ(CubeletPosition(down,front), pd);
    EXPECT_EQ(CubeletPosition(left,front), pl);

    f = back;
    v = vecEdgeEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,back), pu);
    EXPECT_EQ(CubeletPosition(left,back), pr);
    EXPECT_EQ(CubeletPosition(down,back), pd);
    EXPECT_EQ(CubeletPosition(right,back), pl);

    f = up;
    v = vecEdgeEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(back,up), pu);
    EXPECT_EQ(CubeletPosition(right,up), pr);
    EXPECT_EQ(CubeletPosition(front,up), pd);
    EXPECT_EQ(CubeletPosition(left,up), pl);

    f = down;
    v = vecEdgeEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(front,down), pu);
    EXPECT_EQ(CubeletPosition(right,down), pr);
    EXPECT_EQ(CubeletPosition(back,down), pd);
    EXPECT_EQ(CubeletPosition(left,down), pl);

    f = left;
    v = vecEdgeEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,left), pu);
    EXPECT_EQ(CubeletPosition(front,left), pr);
    EXPECT_EQ(CubeletPosition(down,left), pd);
    EXPECT_EQ(CubeletPosition(back,left), pl);

    f = right;
    v = vecEdgeEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,right), pu);
    EXPECT_EQ(CubeletPosition(back,right), pr);
    EXPECT_EQ(CubeletPosition(down,right), pd);
    EXPECT_EQ(CubeletPosition(front,right), pl);
}


TEST(Equivalence,Corner){
    FaceSide f;
    CubeletPosition pul,pur,pdl,pdr;

    f = front;
    vecCletPos v = vecCornerEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,left,front), pul);
    EXPECT_EQ(CubeletPosition(up,right,front), pur);
    EXPECT_EQ(CubeletPosition(down,left,front), pdl);
    EXPECT_EQ(CubeletPosition(down,right,front), pdr);

    f = back;
    v = vecCornerEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,right,back), pul);
    EXPECT_EQ(CubeletPosition(up,left,back), pur);
    EXPECT_EQ(CubeletPosition(down,right,back), pdl);
    EXPECT_EQ(CubeletPosition(down,left,back), pdr);

    f = up;
    v = vecCornerEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(back,left,up), pul);
    EXPECT_EQ(CubeletPosition(back,right,up), pur);
    EXPECT_EQ(CubeletPosition(front,left,up), pdl);
    EXPECT_EQ(CubeletPosition(front,right,up), pdr);

    f = down;
    v = vecCornerEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(front,left,down), pul);
    EXPECT_EQ(CubeletPosition(front,right,down), pur);
    EXPECT_EQ(CubeletPosition(back,left,down), pdl);
    EXPECT_EQ(CubeletPosition(back,right,down), pdr);

    f = left;
    v = vecCornerEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,back,left), pul);
    EXPECT_EQ(CubeletPosition(up,front,left), pur);
    EXPECT_EQ(CubeletPosition(down,back,left), pdl);
    EXPECT_EQ(CubeletPosition(down,front,left), pdr);

    f = right;
    v = vecCornerEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,front,right), pul);
    EXPECT_EQ(CubeletPosition(up,back,right), pur);
    EXPECT_EQ(CubeletPosition(down,front,right), pdl);
    EXPECT_EQ(CubeletPosition(down,back,right), pdr);
}


TEST(Equivalence,Center){
    FaceSide f;
    CubeletPosition pu,pr,pd,pl;

    f = up;
    vecCletPos v = vecCenterEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(back), pu);
    EXPECT_EQ(CubeletPosition(right), pr);
    EXPECT_EQ(CubeletPosition(front), pd);
    EXPECT_EQ(CubeletPosition(left), pl);

    f = down;
    v = vecCenterEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(front), pu);
    EXPECT_EQ(CubeletPosition(right), pr);
    EXPECT_EQ(CubeletPosition(back), pd);
    EXPECT_EQ(CubeletPosition(left), pl);

    f = right;
    v = vecCenterEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up), pu);
    EXPECT_EQ(CubeletPosition(back), pr);
    EXPECT_EQ(CubeletPosition(down), pd);
    EXPECT_EQ(CubeletPosition(front), pl);

    f = left;
    v = vecCenterEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up), pu);
    EXPECT_EQ(CubeletPosition(front), pr);
    EXPECT_EQ(CubeletPosition(down), pd);
    EXPECT_EQ(CubeletPosition(back), pl);

    f = front;
    v = vecCenterEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up), pu);
    EXPECT_EQ(CubeletPosition(right), pr);
    EXPECT_EQ(CubeletPosition(down), pd);
    EXPECT_EQ(CubeletPosition(left), pl);

    f = back;
    v = vecCenterEquivalence<CubeletPosition>(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up), pu);
    EXPECT_EQ(CubeletPosition(left), pr);
    EXPECT_EQ(CubeletPosition(down), pd);
    EXPECT_EQ(CubeletPosition(right), pl);
}

TEST(Equivalence,MidEdge){
    FaceSide f;
    CubeletPosition pul,pur,pdl,pdr;

    f = front;
    vecCletPos v = vecMidEdgeEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,left), pul);
    EXPECT_EQ(CubeletPosition(up,right), pur);
    EXPECT_EQ(CubeletPosition(down,left), pdl);
    EXPECT_EQ(CubeletPosition(down,right), pdr);

    f = back;
    v = vecMidEdgeEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,right), pul);
    EXPECT_EQ(CubeletPosition(up,left), pur);
    EXPECT_EQ(CubeletPosition(down,right), pdl);
    EXPECT_EQ(CubeletPosition(down,left), pdr);

    f = up;
    v = vecMidEdgeEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(back,left), pul);
    EXPECT_EQ(CubeletPosition(back,right), pur);
    EXPECT_EQ(CubeletPosition(front,left), pdl);
    EXPECT_EQ(CubeletPosition(front,right), pdr);

    f = down;
    v = vecMidEdgeEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(front,left), pul);
    EXPECT_EQ(CubeletPosition(front,right), pur);
    EXPECT_EQ(CubeletPosition(back,left), pdl);
    EXPECT_EQ(CubeletPosition(back,right), pdr);

    f = left;
    v = vecMidEdgeEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,back), pul);
    EXPECT_EQ(CubeletPosition(up,front), pur);
    EXPECT_EQ(CubeletPosition(down,back), pdl);
    EXPECT_EQ(CubeletPosition(down,front), pdr);

    f = right;
    v = vecMidEdgeEquivalence<CubeletPosition>(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(CubeletPosition(up,front), pul);
    EXPECT_EQ(CubeletPosition(up,back), pur);
    EXPECT_EQ(CubeletPosition(down,front), pdl);
    EXPECT_EQ(CubeletPosition(down,back), pdr);
}
