/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 17th Apr 2017
 *
 * */

#include "gtest/gtest.h"
#include "cubelet.h"
#include "testcommon.h"


class CubeletTest : public ::testing::Test {
    protected:
        Facelet frr;
        FaceletPosition fp_fu;
        Facelet fwf;
        FaceletPosition fp_uf;
        Facelet fbu;

        FaceletPosition fp_bld;
        FaceletPosition fp_ldb;
        FaceletPosition fp_dbl;
        Facelet fgb;
        Facelet fol;
        Facelet fwd;
        
        CubeletPosition pfrd;
        
        Cubelet cr;
        Cubelet cfu;
        Cubelet cbld;

        CubeletTest(): frr(red, right), fp_fu(front, up), fwf(white, fp_fu), fp_uf(up, front), fbu(blue, fp_uf),
                       fp_bld(back, left, down), fp_ldb(left, down, back), fp_dbl(down, back, left), fgb(green, fp_bld), fol(orange, fp_ldb), fwd(white, fp_dbl),
                       pfrd(front, right, down),
                       cr(frr), cfu(fwf, fbu), cbld(fgb, fol, fwd)
                       {}
};

TEST_F(CubeletTest, constructors) {

    EXPECT_PRED_FORMAT2(checkPrint, "Facelet(s): { (Right, R) }", cr);
    
}

TEST_F(CubeletTest, vecside) {

    EXPECT_EQ(Back, cbld.getFacelet(fp_bld).side());
    EXPECT_EQ(Green, cbld.getFacelet(fp_bld).getColor());
    
    EXPECT_EQ(Left, cbld.getFacelet(fp_ldb).side());
    EXPECT_EQ(Orange, cbld.getFacelet(fp_ldb).getColor());

    EXPECT_EQ(Down, cbld.getFacelet(fp_dbl).side());
    EXPECT_EQ(White, cbld.getFacelet(fp_dbl).getColor());

}

TEST_F(CubeletTest, get) {

    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Center, vecSide = { Right }", cr.getPosition());

    listFaceletPosition lFP;
    lFP.push_back(fp_bld);
    lFP.push_back(fp_ldb);
    lFP.push_back(fp_dbl);

    EXPECT_EQ( lFP, cbld.getFaceletPositionList() );

    vecFacelet vF;
    vF.push_back(fwf);
    vF.push_back(fbu);

    EXPECT_EQ( vF, cfu.getFacelet() );
}

TEST_F(CubeletTest, set) {

    cbld.setPosition(pfrd);
    EXPECT_PRED_FORMAT2(checkPrint, "Position: ptype = Corner, vecSide = { Front Right Down }", cbld.getPosition());

}


TEST_F(CubeletTest, overloading) {
    EXPECT_TRUE(Cubelet(frr) == Cubelet(frr));
    EXPECT_TRUE(Cubelet(frr) != Cubelet(fwf));
}


TEST_F(CubeletTest, CubeletPosition){
    //Create CubeletPositons
    CubeletPosition cp_f(front);
    CubeletPosition cp_fl(front, left);
    CubeletPosition cp_fld(front, left, down);
    CubeletPosition cp_fdl(front, down, left);
    CubeletPosition cp_dfl( down,front, left);

    EXPECT_FALSE( cp_f == cp_fl );
    EXPECT_FALSE( cp_fld != cp_fdl );
    EXPECT_FALSE( cp_dfl != cp_fdl );

}


TEST_F(CubeletTest, vectorinitializer){
    //Create vector of Facelets
    std::vector<Facelet> vf{fgb, fol, fwd};
    Cubelet c1(vf);
    EXPECT_EQ(c1.getFacelet(fp_bld), Facelet(green, fp_bld));
    EXPECT_EQ(c1.getFacelet(fp_ldb), Facelet(orange, fp_ldb));
    EXPECT_EQ(c1.getFacelet(fp_dbl), Facelet(white, fp_dbl));
    EXPECT_THROW( Cubelet(frr, fwf, fgb) , std::runtime_error );
}

TEST_F(CubeletTest, multiplication){
    
    //Center Cubelet rotation
    ASSERT_EQ(Cubelet({front, red}), cr *= up);
    EXPECT_EQ(Cubelet({left, red}), cr *= up );
    ASSERT_EQ(Cubelet({back, red}), cr *= up);
    ASSERT_EQ(CubeletPosition(back), cr.getPosition());

    //Edge Cubelet rotation
    ASSERT_EQ(Cubelet(Facelet( {back,up}, blue), Facelet( {up,back}, white)), cfu*=right);
    ASSERT_EQ(Cubelet(Facelet( {left,up}, blue), Facelet( {up,left}, white)), cfu*=down);
    ASSERT_EQ(Cubelet(Facelet( {down,left}, blue), Facelet( {left,down}, white)), cfu*=back);
    ASSERT_EQ(CubeletPosition(down, left), cfu.getPosition());

    //Corner Cubelet rotation
    ASSERT_EQ(Cubelet( Facelet( {back,up,left}, green), Facelet( {up,left,back}, orange), Facelet( {left,back,up}, white ) ), cbld*=front);
    ASSERT_EQ(Cubelet( Facelet( {up,front,left}, green), Facelet( {front,left,up}, orange), Facelet( {left,up,front}, white ) ), cbld*=left);
    ASSERT_EQ(Cubelet( Facelet( {right,front,up}, green), Facelet( {front,up,right}, orange), Facelet( {up,right,front}, white ) ), cbld*=front);
    ASSERT_EQ(CubeletPosition(front, up, right), cbld.getPosition());
}


TEST(Cubelet, TypeOperator){

    EXPECT_EQ(0, CubeletPosition(front));
    EXPECT_EQ(1, CubeletPosition(back));
    EXPECT_EQ(2, CubeletPosition(up));
    EXPECT_EQ(3, CubeletPosition(down));
    EXPECT_EQ(4, CubeletPosition(left));
    EXPECT_EQ(5, CubeletPosition(right));

    EXPECT_EQ(6, CubeletPosition(front,up));
    EXPECT_EQ(6, CubeletPosition(up,front));
    EXPECT_EQ(7, CubeletPosition(front,down));
    EXPECT_EQ(8, CubeletPosition(front,left));
    EXPECT_EQ(9, CubeletPosition(front,right));
    EXPECT_EQ(10, CubeletPosition(back,up));
    EXPECT_EQ(11, CubeletPosition(back,down));
    EXPECT_EQ(11, CubeletPosition(down,back));
    EXPECT_EQ(12, CubeletPosition(back,left));
    EXPECT_EQ(13, CubeletPosition(back,right));
    EXPECT_EQ(14, CubeletPosition(up,left));
    EXPECT_EQ(15, CubeletPosition(up,right));
    EXPECT_EQ(15, CubeletPosition(right,up));
    EXPECT_EQ(16, CubeletPosition(down,left));
    EXPECT_EQ(17, CubeletPosition(down,right));

    EXPECT_EQ(18, CubeletPosition(front,up,left));
    EXPECT_EQ(18, CubeletPosition(up,left,front));
    EXPECT_EQ(18, CubeletPosition(left,front,up));
    EXPECT_EQ(18, CubeletPosition(front,left,up));
    EXPECT_EQ(18, CubeletPosition(up,front,left));
    EXPECT_EQ(18, CubeletPosition(left,up,front));
    EXPECT_EQ(19, CubeletPosition(front,up,right));
    EXPECT_EQ(20, CubeletPosition(front,down,left));
    EXPECT_EQ(21, CubeletPosition(front,down,right));
    EXPECT_EQ(22, CubeletPosition(back,up,left));
    EXPECT_EQ(23, CubeletPosition(back,up,right));
    EXPECT_EQ(24, CubeletPosition(back,down,left));
    EXPECT_EQ(25, CubeletPosition(back,down,right));

}


TEST(Equivalence,Edge){
    FaceSide f;
    Position pu,pr,pd,pl;

    f = front;
    vecCletPos v = vecEdgeEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(up,front), pu);
    EXPECT_EQ(Position(right,front), pr);
    EXPECT_EQ(Position(down,front), pd);
    EXPECT_EQ(Position(left,front), pl);

    f = back;
    vecEdgeEquPosition(f);
    v = vecEdgeEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(up,back), pu);
    EXPECT_EQ(Position(left,back), pr);
    EXPECT_EQ(Position(down,back), pd);
    EXPECT_EQ(Position(right,back), pl);

    f = up;
    vecEdgeEquPosition(f);
    v = vecEdgeEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(back,up), pu);
    EXPECT_EQ(Position(right,up), pr);
    EXPECT_EQ(Position(front,up), pd);
    EXPECT_EQ(Position(left,up), pl);

    f = down;
    vecEdgeEquPosition(f);
    v = vecEdgeEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(front,down), pu);
    EXPECT_EQ(Position(right,down), pr);
    EXPECT_EQ(Position(back,down), pd);
    EXPECT_EQ(Position(left,down), pl);

    f = left;
    vecEdgeEquPosition(f);
    v = vecEdgeEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(up,left), pu);
    EXPECT_EQ(Position(front,left), pr);
    EXPECT_EQ(Position(down,left), pd);
    EXPECT_EQ(Position(back,left), pl);

    f = right;
    vecEdgeEquPosition(f);
    v = vecEdgeEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(up,right), pu);
    EXPECT_EQ(Position(back,right), pr);
    EXPECT_EQ(Position(down,right), pd);
    EXPECT_EQ(Position(front,right), pl);
}


TEST(Equivalence,Corner){
    FaceSide f;
    Position pul,pur,pdl,pdr;

    f = front;
    vecCletPos v = vecCornerEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(up,left,front), pul);
    EXPECT_EQ(Position(up,right,front), pur);
    EXPECT_EQ(Position(down,left,front), pdl);
    EXPECT_EQ(Position(down,right,front), pdr);

    f = back;
    v = vecCornerEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(up,right,back), pul);
    EXPECT_EQ(Position(up,left,back), pur);
    EXPECT_EQ(Position(down,right,back), pdl);
    EXPECT_EQ(Position(down,left,back), pdr);

    f = up;
    v = vecCornerEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(back,left,up), pul);
    EXPECT_EQ(Position(back,right,up), pur);
    EXPECT_EQ(Position(front,left,up), pdl);
    EXPECT_EQ(Position(front,right,up), pdr);

    f = down;
    v = vecCornerEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(front,left,down), pul);
    EXPECT_EQ(Position(front,right,down), pur);
    EXPECT_EQ(Position(back,left,down), pdl);
    EXPECT_EQ(Position(back,right,down), pdr);

    f = left;
    v = vecCornerEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(up,back,left), pul);
    EXPECT_EQ(Position(up,front,left), pur);
    EXPECT_EQ(Position(down,back,left), pdl);
    EXPECT_EQ(Position(down,front,left), pdr);

    f = right;
    v = vecCornerEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(up,front,right), pul);
    EXPECT_EQ(Position(up,back,right), pur);
    EXPECT_EQ(Position(down,front,right), pdl);
    EXPECT_EQ(Position(down,back,right), pdr);
}


TEST(Equivalence,Center){
    FaceSide f;
    Position pu,pr,pd,pl;

    f = up;
    vecCletPos v = vecCenterEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(back), pu);
    EXPECT_EQ(Position(right), pr);
    EXPECT_EQ(Position(front), pd);
    EXPECT_EQ(Position(left), pl);

    f = down;
    v = vecCenterEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(front), pu);
    EXPECT_EQ(Position(right), pr);
    EXPECT_EQ(Position(back), pd);
    EXPECT_EQ(Position(left), pl);

    f = right;
    v = vecCenterEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(up), pu);
    EXPECT_EQ(Position(back), pr);
    EXPECT_EQ(Position(down), pd);
    EXPECT_EQ(Position(front), pl);

    f = left;
    v = vecCenterEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(up), pu);
    EXPECT_EQ(Position(front), pr);
    EXPECT_EQ(Position(down), pd);
    EXPECT_EQ(Position(back), pl);

    f = front;
    v = vecCenterEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(up), pu);
    EXPECT_EQ(Position(right), pr);
    EXPECT_EQ(Position(down), pd);
    EXPECT_EQ(Position(left), pl);

    f = back;
    v = vecCenterEquPosition(f);
    pu = *v.begin(); pr = *(v.begin()+1); pd = *(v.begin()+2); pl = *(v.begin()+3);
    EXPECT_EQ(Position(up), pu);
    EXPECT_EQ(Position(left), pr);
    EXPECT_EQ(Position(down), pd);
    EXPECT_EQ(Position(right), pl);
}

TEST(Equivalence,MidEdge){
    FaceSide f;
    Position pul,pur,pdl,pdr;

    f = front;
    vecCletPos v = vecMidEdgeEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(up,left), pul);
    EXPECT_EQ(Position(up,right), pur);
    EXPECT_EQ(Position(down,left), pdl);
    EXPECT_EQ(Position(down,right), pdr);

    f = back;
    v = vecMidEdgeEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(up,right), pul);
    EXPECT_EQ(Position(up,left), pur);
    EXPECT_EQ(Position(down,right), pdl);
    EXPECT_EQ(Position(down,left), pdr);

    f = up;
    v = vecMidEdgeEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(back,left), pul);
    EXPECT_EQ(Position(back,right), pur);
    EXPECT_EQ(Position(front,left), pdl);
    EXPECT_EQ(Position(front,right), pdr);

    f = down;
    v = vecMidEdgeEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(front,left), pul);
    EXPECT_EQ(Position(front,right), pur);
    EXPECT_EQ(Position(back,left), pdl);
    EXPECT_EQ(Position(back,right), pdr);

    f = left;
    v = vecMidEdgeEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(up,back), pul);
    EXPECT_EQ(Position(up,front), pur);
    EXPECT_EQ(Position(down,back), pdl);
    EXPECT_EQ(Position(down,front), pdr);

    f = right;
    v = vecMidEdgeEquPosition(f);
    pul = *v.begin(); pur = *(v.begin()+1); pdr = *(v.begin()+2); pdl = *(v.begin()+3);
    EXPECT_EQ(Position(up,front), pul);
    EXPECT_EQ(Position(up,back), pur);
    EXPECT_EQ(Position(down,front), pdl);
    EXPECT_EQ(Position(down,back), pdr);
}
