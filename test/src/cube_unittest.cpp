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

TEST_F(CubeTest, IgnoreThisTest) {

    std::cout << "This is a dummy test. Please ignore it." << std::endl;

}

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
        EXPECT_EQ( Cubelet( f1, f2), cube.getCubelet( fp1.all() ) );
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
        EXPECT_EQ( Cubelet( f1, f2, f3), cube.getCubelet( fp1.all() ) );
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

    Cube cube_old1(cube);
    Cube cube_new1(cube);
    Step s(right, 2, false);
    cube_new1.rotateSide(s);

    EXPECT_EQ(cube_old1.getCubelet({down,right})*left, cube_new1.getCubelet({up,right})*right);
    
    EXPECT_EQ(cube_old1.getCubelet({up,front,right})*right, cube_new1.getCubelet({down,back,right})*left);
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


    Cube cube_old1(cube);
    Cube cube_new1(cube);
    Step s(back, 1, false);
    cube_new1.rotateSide(s);

    EXPECT_EQ(cube_old1.getCubelet({back,right})*front, cube_new1.getCubelet({back,down}));
    
    EXPECT_EQ(cube_old1.getCubelet({up,back,right})*front, cube_new1.getCubelet({down,back,right}));
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

    Cube cube_old1(cube);
    Cube cube_new1(cube);
    Step s(down, 3, false);
    cube_new1.rotateSide(s);

    EXPECT_EQ(cube_old1.getCubelet(down,right)*down, cube_new1.getCubelet(back,down));
    
    EXPECT_EQ(cube_old1.getCubelet(down,back,right)*down, cube_new1.getCubelet(down,back,left));
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


    SetOfColor cWOB( white, orange, blue );
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
    SetOfColor cs1(c1, c2, c3);
    
    EXPECT_EQ( cube.ColorSetToInt(cs1), cube.ColorSetToInt(cp) );


    CubeletPosition cp2(front);
    vecFacelet vFac2 = cube.getCubelet(cp2).getFacelet();
    Color c4 = vFac2[0].getColor();
    SetOfColor cs2(c4);

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
    EXPECT_EQ(Cube::getFaceletPosition(45), FaceletPosition(down,right,back));

    //Edge Positions
    EXPECT_EQ(Cube::getFaceletPosition(22), FaceletPosition(left, front));
    EXPECT_EQ(Cube::getFaceletPosition(12), FaceletPosition(back, left));

    //Corner Positions
    EXPECT_EQ(Cube::getFaceletPosition(35), FaceletPosition(back,up,right));

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



TEST_F(CubeTest, getFaceletPositions)
{
    CubeletPosition cp1(front);
    lFletPos lfp1 = Cube::getFaceletPositions(cp1);
    auto it1 = lfp1.begin();
    EXPECT_EQ(*it1, FaceletPosition(front));

    CubeletPosition cp2(up,back);
    lFletPos lfp2 = Cube::getFaceletPositions(cp2);
    auto it2 = lfp2.begin();
    EXPECT_EQ(*it2, FaceletPosition(back,up));
    it2++;
    EXPECT_EQ(*it2, FaceletPosition(up,back));

    CubeletPosition cp3(left,undefside,down);
    lFletPos lfp3 = Cube::getFaceletPositions(cp3);
    auto it3 = lfp3.begin();
    EXPECT_EQ(*it3, FaceletPosition(down,left));
    it3++;
    EXPECT_EQ(*it3, FaceletPosition(left,down));

    CubeletPosition cp4(front,right,undefside);
    lFletPos lfp4 = Cube::getFaceletPositions(cp4);
    auto it4 = lfp4.begin();
    EXPECT_EQ(*it4, FaceletPosition(front,right));
    it4++;
    EXPECT_EQ(*it4, FaceletPosition(right,front));

    CubeletPosition cp5(down,left,back);
    lFletPos lfp5 = Cube::getFaceletPositions(cp5);
    auto it5 = lfp5.begin();
    EXPECT_EQ(*it5, FaceletPosition(back,down,left));
    it5++;
    EXPECT_EQ(*it5, FaceletPosition(down,left,back));
    it5++;
    EXPECT_EQ(*it5, FaceletPosition(left,back,down));
}


TEST_F(CubeTest, CollectionWrapper__are_opposite)
{
    CollectionWrapper<Color, true> cw(&cube);
    EXPECT_TRUE( cw.are_opposite(white, yellow) );
    EXPECT_TRUE( cw.are_opposite(red, orange) );
    EXPECT_TRUE( cw.are_opposite(blue, green) );
    EXPECT_TRUE( cw.any_opposite(blue, green, red) );
    EXPECT_TRUE( cw.any_opposite(red, yellow, orange) );
    EXPECT_FALSE( cw.are_opposite(white, orange) );
    EXPECT_FALSE( cw.are_opposite(yellow, orange) );
    EXPECT_FALSE( cw.are_opposite(blue, red) );
    EXPECT_FALSE( cw.any_opposite(yellow, green, red) );
    EXPECT_FALSE( cw.any_opposite(red, yellow, blue) );

    CollectionWrapper<FaceSide, false> cwf;
    EXPECT_TRUE( cwf.are_opposite(left, right) );
    EXPECT_TRUE( cwf.any_opposite(up, down, front) );
    EXPECT_FALSE( cwf.are_opposite(back, down) );
    EXPECT_FALSE( cwf.any_opposite(back, down, right) );
}


TEST_F(CubeTest, CollectionWrapper__size_t)
{
#define WRAPPERSIZE_TEST(T,b,x,n,...)\
    CollectionWrapper<T,b> x(__VA_ARGS__);\
    EXPECT_EQ(x,n);


    //CubeletType, single Color
    WRAPPERSIZE_TEST(Color,false,cwcn,-1,&cube,undefcol);
    WRAPPERSIZE_TEST(Color,false,cwcn0,0,&cube,white);
    WRAPPERSIZE_TEST(Color,false,cwcn1,1,&cube,yellow);
    WRAPPERSIZE_TEST(Color,false,cwcn2,2,&cube,orange);
    WRAPPERSIZE_TEST(Color,false,cwcn3,3,&cube,red);
    WRAPPERSIZE_TEST(Color,false,cwcn4,4,&cube,green);
    WRAPPERSIZE_TEST(Color,false,cwcn5,5,&cube,blue);
    WRAPPERSIZE_TEST(Color,false,cwcn1_1,1,&cube,yellow,undefcol);
    WRAPPERSIZE_TEST(Color,false,cwcn4_1,4,&cube,green,undefcol,undefcol);

    //CubeletType, double Color
    WRAPPERSIZE_TEST(Color,false,cwcn_1,-1,&cube,undefcol,undefcol);
    WRAPPERSIZE_TEST(Color,false,cwcn6,6,&cube,white,orange);
    WRAPPERSIZE_TEST(Color,false,cwcn7,7,&cube,white,red);
    WRAPPERSIZE_TEST(Color,false,cwcn7_1,7,&cube,red,white);
    WRAPPERSIZE_TEST(Color,false,cwcn8,8,&cube,white,green);
    WRAPPERSIZE_TEST(Color,false,cwcn9,9,&cube,white,blue);
    WRAPPERSIZE_TEST(Color,false,cwcn9_1,9,&cube,white,blue,undefcol);
    WRAPPERSIZE_TEST(Color,false,cwcn10,10,&cube,yellow,orange);
    WRAPPERSIZE_TEST(Color,false,cwcn11,11,&cube,yellow,red);
    WRAPPERSIZE_TEST(Color,false,cwcn11_1,11,&cube,red,yellow);
    WRAPPERSIZE_TEST(Color,false,cwcn12,12,&cube,yellow,green);
    WRAPPERSIZE_TEST(Color,false,cwcn13,13,&cube,yellow,blue);
    WRAPPERSIZE_TEST(Color,false,cwcn13_1,13,&cube,yellow,undefcol,blue);
    WRAPPERSIZE_TEST(Color,false,cwcn14,14,&cube,orange,green);
    WRAPPERSIZE_TEST(Color,false,cwcn15,15,&cube,orange,blue);
    WRAPPERSIZE_TEST(Color,false,cwcn15_1,15,&cube,blue,orange);
    WRAPPERSIZE_TEST(Color,false,cwcn16,16,&cube,red,green);
    WRAPPERSIZE_TEST(Color,false,cwcn17,17,&cube,red,blue);
    WRAPPERSIZE_TEST(Color,false,cwcn17_1,17,&cube,blue,red);

    //CubeletType, triple Color
    WRAPPERSIZE_TEST(Color,false,cwcn_2,-1,&cube,undefcol,undefcol,undefcol);
    WRAPPERSIZE_TEST(Color,false,cwcn18,18,&cube,white,orange,green);
    WRAPPERSIZE_TEST(Color,false,cwcn19,19,&cube,white,orange,blue);
    WRAPPERSIZE_TEST(Color,false,cwcn20,20,&cube,white,red,green);
    WRAPPERSIZE_TEST(Color,false,cwcn21,21,&cube,white,red,blue);
    WRAPPERSIZE_TEST(Color,false,cwcn22,22,&cube,yellow,orange,green);
    WRAPPERSIZE_TEST(Color,false,cwcn23,23,&cube,yellow,orange,blue);
    WRAPPERSIZE_TEST(Color,false,cwcn24,24,&cube,yellow,red,green);
    WRAPPERSIZE_TEST(Color,false,cwcn25,25,&cube,yellow,red,blue);


    //FaceletType, single Color
    WRAPPERSIZE_TEST(Color,true,cwcf,-1,&cube,undefcol);
    WRAPPERSIZE_TEST(Color,true,cwcf0,0,&cube,white);
    WRAPPERSIZE_TEST(Color,true,cwcf1,1,&cube,yellow);
    WRAPPERSIZE_TEST(Color,true,cwcf2,2,&cube,orange);
    WRAPPERSIZE_TEST(Color,true,cwcf3,3,&cube,red);
    WRAPPERSIZE_TEST(Color,true,cwcf4,4,&cube,green);
    WRAPPERSIZE_TEST(Color,true,cwcf5,5,&cube,blue);
    WRAPPERSIZE_TEST(Color,true,cwcf0_1,0,&cube,white,undefcol);
    WRAPPERSIZE_TEST(Color,true,cwcf3_1,3,&cube,red,undefcol,undefcol);

    //FaceletType, double Color
    WRAPPERSIZE_TEST(Color,true,cwcf6, 6,&cube, white, orange);
    WRAPPERSIZE_TEST(Color,true,cwcf7, 7,&cube, white, red);
    WRAPPERSIZE_TEST(Color,true,cwcf8, 8,&cube, white, green);
    WRAPPERSIZE_TEST(Color,true,cwcf9, 9,&cube, white, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf10, 10,&cube, yellow, orange);
    WRAPPERSIZE_TEST(Color,true,cwcf11, 11,&cube, yellow, red);
    WRAPPERSIZE_TEST(Color,true,cwcf11_1, 11,&cube, yellow, red, undefcol);
    WRAPPERSIZE_TEST(Color,true,cwcf12, 12,&cube, yellow, green);
    WRAPPERSIZE_TEST(Color,true,cwcf13, 13,&cube, yellow, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf14, 14,&cube, orange, white);
    WRAPPERSIZE_TEST(Color,true,cwcf15, 15,&cube, orange, yellow);
    WRAPPERSIZE_TEST(Color,true,cwcf16, 16,&cube, orange, green);
    WRAPPERSIZE_TEST(Color,true,cwcf17, 17,&cube, orange, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf18, 18,&cube, red, white);
    WRAPPERSIZE_TEST(Color,true,cwcf19, 19,&cube, red, yellow);
    WRAPPERSIZE_TEST(Color,true,cwcf20, 20,&cube, red, green);
    WRAPPERSIZE_TEST(Color,true,cwcf21, 21,&cube, red, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf21_1, 21,&cube, red, blue, undefcol);
    WRAPPERSIZE_TEST(Color,true,cwcf22, 22,&cube, green, white);
    WRAPPERSIZE_TEST(Color,true,cwcf23, 23,&cube, green, yellow);
    WRAPPERSIZE_TEST(Color,true,cwcf24, 24,&cube, green, orange);
    WRAPPERSIZE_TEST(Color,true,cwcf25, 25,&cube, green, red);
    WRAPPERSIZE_TEST(Color,true,cwcf26, 26,&cube, blue, white);
    WRAPPERSIZE_TEST(Color,true,cwcf27, 27,&cube, blue, yellow);
    WRAPPERSIZE_TEST(Color,true,cwcf28, 28,&cube, blue, orange);
    WRAPPERSIZE_TEST(Color,true,cwcf29, 29,&cube, blue, red);
    WRAPPERSIZE_TEST(Color,true,cwcf29_1, 29,&cube, blue, undefcol, red);

    //FaceletType, Triple Color
    WRAPPERSIZE_TEST(Color,true,cwcf30, 30,&cube, white, orange, green);
    WRAPPERSIZE_TEST(Color,true,cwcf30_1, 30,&cube, white, green, orange);
    WRAPPERSIZE_TEST(Color,true,cwcf31, 31,&cube, white, orange, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf31_1, 31,&cube, white, blue, orange);
    WRAPPERSIZE_TEST(Color,true,cwcf32, 32,&cube, white, red, green);
    WRAPPERSIZE_TEST(Color,true,cwcf32_1, 32,&cube, white, green, red);
    WRAPPERSIZE_TEST(Color,true,cwcf33, 33,&cube, white, red, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf33_1, 33,&cube, white, blue, red);
    WRAPPERSIZE_TEST(Color,true,cwcf34, 34,&cube, yellow, orange, green);
    WRAPPERSIZE_TEST(Color,true,cwcf35, 35,&cube, yellow, orange, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf36, 36,&cube, yellow, red, green);
    WRAPPERSIZE_TEST(Color,true,cwcf37, 37,&cube, yellow, red, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf38, 38,&cube, orange, white, green);
    WRAPPERSIZE_TEST(Color,true,cwcf39, 39,&cube, orange, white, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf40, 40,&cube, orange, yellow, green);
    WRAPPERSIZE_TEST(Color,true,cwcf41, 41,&cube, orange, yellow, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf42, 42,&cube, red, white, green);
    WRAPPERSIZE_TEST(Color,true,cwcf42_1, 42,&cube, red, green, white);
    WRAPPERSIZE_TEST(Color,true,cwcf43, 43,&cube, red, white, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf44, 44,&cube, red, yellow, green);
    WRAPPERSIZE_TEST(Color,true,cwcf44_1, 44,&cube, red, green, yellow);
    WRAPPERSIZE_TEST(Color,true,cwcf45, 45,&cube, red, yellow, blue);
    WRAPPERSIZE_TEST(Color,true,cwcf46, 46,&cube, green, white, orange);
    WRAPPERSIZE_TEST(Color,true,cwcf47, 47,&cube, green, white, red);
    WRAPPERSIZE_TEST(Color,true,cwcf48, 48,&cube, green, yellow, orange);
    WRAPPERSIZE_TEST(Color,true,cwcf49, 49,&cube, green, yellow, red);
    WRAPPERSIZE_TEST(Color,true,cwcf50, 50,&cube, blue, white, orange);
    WRAPPERSIZE_TEST(Color,true,cwcf51, 51,&cube, blue, white, red);
    WRAPPERSIZE_TEST(Color,true,cwcf52, 52,&cube, blue, yellow, orange);
    WRAPPERSIZE_TEST(Color,true,cwcf53, 53,&cube, blue, yellow, red);



#undef  WRAPPERSIZE_TEST
}
