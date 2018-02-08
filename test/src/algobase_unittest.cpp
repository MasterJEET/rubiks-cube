/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 24th Jun 2017
 *
 * */

#include "algobase.h"
#include "gtest/gtest.h"

using namespace AlgoBase;

class PrimitiveTest : public ::testing::Test {
    protected:

        Cube C;
        Primitive P;

        PrimitiveTest()
        {
            std::string home = getHome();
            std::string path( home + "/test/dat/cube_linear.dat" );
            C = Cube(path);
        }


};


TEST(Primitive, SubBasics)
{
    std::cout << "Primitive.SubBasics is a dummy test. Please ignore it." << std::endl;
    /* Following line should never throw, but it does. Default constructor for Cube has been
     * verified to be working correctly in test Cube.Cube (cube_unittest.cpp). Following is
     * just a false test, please ignore.
     * */
    EXPECT_NO_THROW(Cube C);
}


TEST_F(PrimitiveTest, Cell)
{
    FaceletPosition fp0(front, down, left);
    FaceletPosition fp(front,down);


    /*
     *
     * FROM ELSEWHERE TO FRONT FACESIDE
     *
     * */

    //{f1, f2, f3} --> {front, down, left}
#   define  TEST_CORNER(f1, f2, f3, fp, seq, cl, cl_new)\
    \
    FaceletPosition fp(f1, f2, f3);\
    StepSequence seq = P.getSequence( fp, fp0 );\
    Cubelet cl = C.getCubelet(fp);\
    C.update(seq);\
    Cubelet cl_new( C.getCubelet(fp0));\
    EXPECT_TRUE( haveSameColors(cl, cl_new) );\
    EXPECT_EQ( cl.getFacelet(fp).getColor(), cl_new.getFacelet(fp0).getColor() );

    TEST_CORNER(down,back,left, fp1,seq1,cl1,cl1_new);
    TEST_CORNER(left,down,back, fp2,seq2,cl2,cl2_new);
    TEST_CORNER(back,left,down, fp3,seq3,cl3,cl3_new);

#   undef TEST_CORNER


    //{f1, f2} --> {front,down}
#   define TEST_EDGE(f1,f2, efp,eseq,ecl,ecl_new)\
    \
    FaceletPosition efp(down, back);\
    StepSequence eseq = P.getSequence( efp, fp );\
    Cubelet ecl = C.getCubelet(efp);\
    C.update(eseq);\
    Cubelet ecl_new( C.getCubelet(fp));\
    EXPECT_TRUE( haveSameColors(ecl, ecl_new) );\
    EXPECT_EQ( ecl.getFacelet(efp).getColor(), ecl_new.getFacelet(fp).getColor() );

    TEST_EDGE(down,back, efp1,eseq1,ecl1,ecl1_new);
    TEST_EDGE(back,down, efp2,eseq2,ecl2,ecl2_new);
    TEST_EDGE(left,down, efp3,eseq3,ecl3,ecl3_new);
    TEST_EDGE(down,left, efp4,eseq4,ecl4,ecl4_new);

#   undef   TEST_EDGE


}


TEST_F(PrimitiveTest, Basics)
{
    FaceletPosition fp_to_corner(front,down,left);

    //{f1, f2, f3} --> {front,down,left}

#   define CORNER_TEST(f1, f2, f3, fp, seq, cl, cl_new)\
    \
    FaceletPosition fp(f1, f2, f3);\
    StepSequence seq = P.getSequence(fp,fp_to_corner);\
    Cubelet cl = C.getCubelet(fp);\
    C.update(seq);\
    Cubelet cl_new( C.getCubelet(fp_to_corner) );\
    EXPECT_TRUE( haveSameColors(cl, cl_new) );\
    EXPECT_EQ( cl.getFacelet(fp).getColor(), cl_new.getFacelet(fp_to_corner).getColor());

    CORNER_TEST(up, back, left, cfp1, cseq1, ccl1, ccl1_new);
    CORNER_TEST(back, up, left, cfp2, cseq2, ccl2, ccl2_new);
    CORNER_TEST(left, back, up, cfp3, cseq3, ccl3, ccl3_new);
    CORNER_TEST(up, right, back, cfp4, cseq4, ccl4, ccl4_new);
    CORNER_TEST(down, right, back, cfp5, cseq5, ccl5, ccl5_new);
    CORNER_TEST(front, up, left, cfp6, cseq6, ccl6, ccl6_new);
    CORNER_TEST(up, left, front, cfp7, cseq7, ccl7, ccl7_new);
    CORNER_TEST(left, front, up, cfp8, cseq8, ccl8, ccl8_new);
    CORNER_TEST(front, up, right, cfp9, cseq9, ccl9, ccl9_new);
    CORNER_TEST(down, right, front, cfp10, cseq10, ccl10, ccl10_new);
    CORNER_TEST(left, front, down, cfp11, cseq11, ccl11, ccl11_new);

#   undef   CORNER_TEST


    FaceletPosition fp_to_edge(front,down);
    //{f1, f2} --> {front,down}

#   define  EDGE_TEST(f1, f2, fp, seq, cl, cl_new)\
    \
    FaceletPosition fp(f1, f2);\
    StepSequence seq = P.getSequence(fp,fp_to_edge);\
    Cubelet cl = C.getCubelet(fp);\
    C.update(seq);\
    Cubelet cl_new( C.getCubelet(fp_to_edge));\
    EXPECT_TRUE( haveSameColors(cl, cl_new));\
    EXPECT_EQ( cl.getFacelet(fp).getColor(), cl_new.getFacelet(fp_to_edge).getColor() );

    EDGE_TEST(back, left, fp1, seq1, cl1, cl1_new);
    EDGE_TEST(up, back, fp2, seq2, cl2, cl2_new);
    EDGE_TEST(back, right, fp3, seq3, cl3, cl3_new);
    EDGE_TEST(back, down, fp7, seq7, cl7, cl7_new);
    EDGE_TEST(front, left, fp4, seq4, cl4, cl4_new);
    EDGE_TEST(front, right, fp5, seq5, cl5, cl5_new);
    EDGE_TEST(up, front, fp6, seq6, cl6, cl6_new);
    EDGE_TEST(down, front, fp8, seq8, cl8, cl8_new);
    EDGE_TEST(up, left, fp9, seq9, cl9, cl9_new);
    EDGE_TEST(up, right, fp10, seq10, cl10, cl10_new);
    EDGE_TEST(down, right, fp11, seq11, cl11, cl11_new);
    EDGE_TEST(left,down, fp12, seq12, cl12, cl12_new);
    EDGE_TEST(down,left, fp13, seq13, cl13, cl13_new);

#   undef EDGE_TEST

}


TEST_F(PrimitiveTest, AnyToAny)
{

    //{f1,f2,f3} --> {t1,t2,t3}
#   define  ANYCORNER_TEST(f1,f2,f3, t1,t2,t3, from,to,cl,seq,cl_new)\
    FaceletPosition from(f1,f2,f3);\
    FaceletPosition to(t1,t2,t3);\
    Cubelet cl = C.getCubelet(from);\
    StepSequence seq = P.getSequence(from, to);\
    C.update(seq);\
    Cubelet cl_new = C.getCubelet(to);\
    EXPECT_TRUE( haveSameColors(cl, cl_new));\
    EXPECT_EQ( cl.getFacelet(from).getColor(), cl_new.getFacelet(to).getColor() );

    ANYCORNER_TEST(down,back,right, left,front,up, from1,to1,cl1,seq1,cl1_new);
    ANYCORNER_TEST(up,left,back, right,front,down, from2,to2,cl2,seq2,cl2_new);
    ANYCORNER_TEST(left,back,down, left,front,down, from3,to3,cl3,seq3,cl3_new);

#   undef   ANYCORNER_TEST

#   define  ANYEDGE_TEST(f1,f2, t1,t2, from,to,cl,seq,cl_new)\
    FaceletPosition from(f1,f2);\
    FaceletPosition to(t1,t2);\
    Cubelet cl = C.getCubelet(from);\
    StepSequence seq = P.getSequence(from, to);\
    C.update(seq);\
    Cubelet cl_new = C.getCubelet(to);\
    EXPECT_TRUE( haveSameColors(cl, cl_new));\
    EXPECT_EQ( cl.getFacelet(from).getColor(), cl_new.getFacelet(to).getColor() );

    ANYEDGE_TEST(front,up, back,right, efrom1,eto1,ecl1,eseq1,ecl1_new);
    ANYEDGE_TEST(down,left, right,back, efrom2,eto2,ecl2,eseq2,ecl2_new);
    ANYEDGE_TEST(front,left, front,right, efrom3,eto3,ecl3,eseq3,ecl3_new);

#   undef   ANYEDGE_TEST

}


TEST_F(PrimitiveTest, howTo)
{

    //Back equivalent
    FaceSide from1 = right;
    FaceSide to1 = left;

    Step s1 = P.howTo(from1, to1);
    Cubelet cfrom1 = C.getCubelet(from1);
    C.rotate(s1);
    Cubelet cto1 = C.getCubelet(to1);

    EXPECT_TRUE(haveSameColors(cfrom1, cto1));

    //Up Equivalent
    FaceSide from2 = back;
    FaceSide to2 = up;

    Step s2 = P.howTo(from2, to2);
    Cubelet cfrom2 = C.getCubelet(from2);
    C.rotate(s2);
    Cubelet cto2 = C.getCubelet(to2);

    EXPECT_TRUE(haveSameColors(cfrom2, cto2));

    //Right Equivalent
    FaceSide from3 = right;
    FaceSide to3 = down;

    Step s3 = P.howTo(from3, to3);
    Cubelet cfrom3 = C.getCubelet(from3);
    C.rotate(s3);
    Cubelet cto3 = C.getCubelet(to3);

    EXPECT_TRUE(haveSameColors(cfrom3, cto3));

    //Down Equivalent
    FaceSide from4 = down;
    FaceSide to4 = right;

    Step s4 = P.howTo(from4, to4);
    Cubelet cfrom4 = C.getCubelet(from4);
    C.rotate(s4);
    Cubelet cto4 = C.getCubelet(to4);

    EXPECT_TRUE(haveSameColors(cfrom4, cto4));

    //Down Equivalent
    FaceSide from5 = back;
    FaceSide to5 = down;

    Step s5 = P.howTo(from5, to5);
    Cubelet cfrom5 = C.getCubelet(from5);
    C.rotate(s5);
    Cubelet cto5 = C.getCubelet(to5);

    EXPECT_TRUE(haveSameColors(cfrom5, cto5));
    
}


TEST_F(PrimitiveTest, getSeqToStandard)
{
#   define SEQSTD_TEST(fp,cl,seq,cl_new, ...)\
    FaceletPosition fp( __VA_ARGS__ );\
    Cubelet cl = C.getCubelet(fp);\
    StepSequence seq = P.getSeqToStandard(fp);\
    C.rotate(seq);\
    Cubelet cl_new = C.getCubelet(fpto);\
    EXPECT_TRUE( haveSameColors(cl, cl_new));\
    EXPECT_EQ( cl.getFacelet(fp).getColor(), cl_new.getFacelet(fpto).getColor() );

    //Corner Cublets
    FaceletPosition fpto(front,down,left);

    SEQSTD_TEST(fp1,cl1,seq1,cl1_new, back,right,up);
    SEQSTD_TEST(fp2,cl2,seq2,cl2_new, back,left,down);
    SEQSTD_TEST(fp3,cl3,seq3,cl3_new, front,down,left);
    SEQSTD_TEST(cfp1,ccl1,cseq1,ccl1_new, right,down,front);

    //Edge Cubelets
    fpto = FaceletPosition(front,down);
    SEQSTD_TEST(fp4,cl4,seq4,cl4_new, right,front);
    SEQSTD_TEST(fp5,cl5,seq5,cl5_new, down,back);
    SEQSTD_TEST(fp6,cl6,seq6,cl6_new, front,down);

#   undef SEQSTD_TEST

}


//TEST(Primitive, getStesToReference)
//{
//    CubeletPosition cpFrom(up,back,left);
//    CubeletPosition cpTo(up,back,right);
//
//    StepSequence seq = Primitive::getStepsToReference(cpFrom, cpTo);
//    Cube C;
//    Cubelet clFromOld = C.getCubelet(cpFrom);
//    Cubelet clToOld = C.getCubelet(cpTo);
//    C.rotate(seq);
//
//    EXPECT_TRUE(haveSameColors(clFromOld, C.getCubelet(down,back,left)));
//    EXPECT_TRUE(haveSameColors(clToOld, C.getCubelet(down,front,left)));
//
//
//    CubeletPosition cpFrom1(down,back,left);
//    CubeletPosition cpTo1(down,back,right);
//
//    StepSequence seq1 = Primitive::getStepsToReference(cpFrom1, cpTo1);
//    Cubelet clFromOld1 = C.getCubelet(cpFrom1);
//    Cubelet clToOld1 = C.getCubelet(cpTo1);
//    C.rotate(seq1);
//
//    EXPECT_TRUE(haveSameColors(clFromOld1, C.getCubelet(down,back,left)));
//    EXPECT_TRUE(haveSameColors(clToOld1, C.getCubelet(down,front,left)));
//}


TEST_F(PrimitiveTest, getRotationalReverseSeq)
{
    Step F(front);
    Step f(front,false);
    Step mbb(back,false,2,true);
    Step U(up);
    Step mU(up,true,1,true);
    Step u(up,false);
    Step d(down,false);
    Step md(down,false,1,true);
    Step L(left);
    Step l(left,false);
    Step mR(right,true,1,true);
    Step r(right,false);

#   define  REVERSE_TEST(fp,seq,cl,rev,cl_new, ...)\
    FaceletPosition fp(__VA_ARGS__);\
    Cubelet cl = C.getCubelet(fp);\
    C.rotate(seq);\
    StepSequence rev = P.getRotationalReverseSeq(seq);\
    C.rotate(rev);\
    Cubelet cl_new = C.getCubelet(fp);\
    EXPECT_TRUE( haveSameColors(cl, cl_new));\
    EXPECT_EQ( cl.getFacelet(fp).getColor(), cl_new.getFacelet(fp).getColor() );

    StepSequence seq1({F,f,U,md});
    REVERSE_TEST(fp1,seq1,cl1,rev1,cl1_new, back,left,down);

    StepSequence seq2({f,d,L,u,mbb,mU,r});
    REVERSE_TEST(fp2,seq2,cl2,rev2,cl2_new, right,up);

    StepSequence seq3({mU,L,d,l,mR});
    REVERSE_TEST(fp3,seq3,cl3,rev3,cl3_new, down);


#   undef   REVERSE_TEST

}
