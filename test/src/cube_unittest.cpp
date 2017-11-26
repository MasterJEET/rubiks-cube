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
        FaceletPosition fp1( vf->at(0), vf->at(1), vf->at(2) );   FaceletPosition fp2( vf->at(1), vf->at(0), vf->at(2) );   FaceletPosition fp3( vf->at(2), vf->at(0), vf->at(1) );
        Facelet f1(fp1, vc->at(0) );   Facelet f2(fp2, vc->at(1) );   Facelet f3(fp3, vc->at(2) );
        EXPECT_EQ( Cubelet( f1, f2, f3), cube.getCubelet( fp1 ) );
    }
    }
    

}


TEST_F(CubeTest, show){
    cube.show(front);
    cube.show(back);
    cube.show(left);
    cube.show(right);
    cube.show(up);
    cube.show(down);
}


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
