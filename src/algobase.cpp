/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Feb 2018
 *
 * */

#include "algobase.h"

using namespace AlgoBase;

Primitive::Primitive()
{
    init();

    initClet();
}

void Primitive::init()
{

    //Frequent steps
    Step d(down, false);
    Step b(back, false);
    Step D(down);
    Step L(left);
    Step B(back);
    Step l(left, false);
    Step bb(back, 2, false);
    Step mF(front, true, 1, true);
    Step mf(front, false, 1, true);
    Step mff(front, false, 2, true);
    Step mr(right, false, 1, true);
    Step mR(right, true, 1, true);

    FaceletPosition P_endc(front, left, down);
    FaceletPosition P_ende(front, down);

    /*
     * FROM BACK TO FRONT FACE. CORNER CUBELETS.
     *
     * */


    //Steps for moving Cubelet from P_start(down,back,left) to P_end(front,left,down).
    //In the end, no Cubelets on front Face except the one at P_end should get affected
#   define  ADD_MOVE_CORNER(f1,f2,f3, cfp,ckey,cseq)\
    FaceletPosition cfp(f1,f2,f3);\
    Relation ckey(cfp, P_endc);\
    mRelStep[ ckey ] = cseq;

    StepSequence cseq1({d, b, D});
    ADD_MOVE_CORNER(down,back,left, cfp1,ckey1,cseq1);

    StepSequence cseq2({L, B, l});
    ADD_MOVE_CORNER(left,back,down, cfp2,ckey2,cseq2);

    //There are two similar ways of doing this (keeping here only one). In future keep a multimap
    //and choose one method which suits best as per the situation
    StepSequence cseq3({B, L, bb, l, d, b, D});
    ADD_MOVE_CORNER(back,left,down, cfp3,ckey3,cseq3);

#   undef ADD_MOVE_CORNER


    /*
     * BACK --> FRONT. EDGE CUBELETS.
     *
     * */

#   define  ADD_MOVE_EDGE(f1,f2, efp,ekey,eseq)\
    FaceletPosition efp(f1, f2);\
    Relation ekey(efp, P_ende);\
    mRelStep[ ekey ] = eseq;

    //{down,back} --> {front,down}, there is another similar way
    StepSequence eseq1({D, mf, d});
    ADD_MOVE_EDGE(down,back, efp1,ekey1,eseq1);

    StepSequence eseq2({mr, bb, mR});
    ADD_MOVE_EDGE(back,down, efp2,ekey2,eseq2);


    /*
     * MID --> FRONT. EDGE CUBELETS.
     *
     * */

    StepSequence eseq3({mF, d, mf, D});
    ADD_MOVE_EDGE(left,down, efp3,ekey3,eseq3);

    StepSequence eseq4({mff, D, mF, d});
    ADD_MOVE_EDGE(down,left, efp4,ekey4,eseq4);

#   undef ADD_MOVE_EDGE

}


void Primitive::initClet()
{

    Step B(back);       //clockwise
    Step Bm(back,true,1,true);
    Step b(back,false); //anti-clockwise
    Step bm(back,false,1,true);
    Step bb(back,false,2);
    Step bbm(back,false,2,true);
    Step U(up);
    Step u(up,false);
    Step R(right);
    Step r(right,false);
    Step L(left);
    Step l(left,false);
    Step Um(up,true,1,true);    //clockwise rotation of mid face
    Step um(up,false,1,true);   //anti-clockwise rotation of mid face
    Step fm(front,false,1,true);
    Step Rm(right,true,1,true);
    Step rm(right,false,1,true);

    CubeletPosition cp_to(down,back,left);

#   define  MOVE_CORNER(f1,f2,f3, cp,ckey,cseq)\
    CubeletPosition cp(f1,f2,f3);\
    CletRelation ckey(cp, cp_to);\
    mCletStep[ ckey ] = cseq;

    /*
     * OF CORNER CUBELETS, BACK --> BACK
     *
     * */

    StepSequence cseq1({B});
    MOVE_CORNER(up,back,left, cp1,ckey1,cseq1);

    StepSequence cseq2({bb});
    MOVE_CORNER(up,back,right, cp2,ckey2,cseq2);

    StepSequence cseq3({b});
    MOVE_CORNER(right,down,back, cp3,ckey3,cseq3);

    /*
     * OF CORNER CUBELETS, FRONT --> BACK
     *
     * */

    StepSequence cseq4({U,B,u});
    MOVE_CORNER(front,up,left, cp4,ckey4,cseq4);

    StepSequence cseq5({u,bb,U});
    MOVE_CORNER(front,up,right, cp5,ckey5,cseq5);

    StepSequence cseq6({r,b,R});
    MOVE_CORNER(front,down,right, cp6,ckey6,cseq6);

    //{front,down,left} --> {down,back,left}, This is special cause finally Cubelet will moved to initial position
    StepSequence cseq7({L,b,l});
    MOVE_CORNER(front,down,left, cp7,ckey7,cseq7);

#   undef MOVE_CORNER


    CubeletPosition cp_to_edge (down,back);

#   define  MOVE_EDGE(f1,f2, ep,ekey,eseq)\
    CubeletPosition ep(f1,f2);\
    CletRelation ekey(ep, cp_to_edge);\
    mCletStep[ ekey ] = eseq;


    /*
     * OF EDGE CUBELETS, BACK --> BACK
     *
     * */

    StepSequence eseq1({B});
    MOVE_EDGE(back,left, ep1,ekey1,eseq1);

    StepSequence eseq2({bb});
    MOVE_EDGE(back,up, ep2,ekey2,eseq2);

    StepSequence eseq3({b});
    MOVE_EDGE(back,right, ep3,ekey3,eseq3);

    /*
     * OF EDGE CUBELETS, FRONT --> BACK
     *
     * */

    StepSequence eseq4({Um,B,um});
    MOVE_EDGE(front,left, ep4,ekey4,eseq4);

    StepSequence eseq5({um,b,Um});
    MOVE_EDGE(front,right, ep5,ekey5,eseq5);

    StepSequence eseq6({u,fm,U,bb});
    MOVE_EDGE(up,front, ep6,ekey6,eseq6);

    //This is a special case as finally Cubelet will be brought to initial position
    StepSequence eseq7({rm,bb,Rm});
    MOVE_EDGE(down,front, ep7,ekey7,eseq7);

    /*
     * OF EDGE CUBELETS, MID --> MID
     *
     * */

    StepSequence eseq8({Bm});
    MOVE_EDGE(up,left, ep8,ekey8,eseq8);

    StepSequence eseq9({bbm});
    MOVE_EDGE(up,right, ep9,ekey9,eseq9);

    StepSequence eseq10({bm});
    MOVE_EDGE(down,right, ep10,ekey10,eseq10);


#   undef   MOVE_EDGE

}



Step Primitive::howTo(const FaceSide& from, const FaceSide& to)
{
    Step s;

    FaceSide u,r,d,l;
    FaceSide b = opposite(to);
    setEquivalentFaceSide(to,u,r,d,l);

    if(from == u){
        s = Step(l);
    }
    else if(from == r){
        s = Step(u);
    }
    else if(from == d){
        s = Step(r);
    }
    else if(from == l){
        s = Step(d);
    }
    else if(from == b){
        s = Step(u,false,2);
    }
    else{
        s.f = undefside;
    }

    return s;
}

StepSequence Primitive::getSeqToStandard(FaceletPosition fp_from)
{

    StepSequence sqRet;

    Step s1 = howTo(fp_from.first(), front);
    Step s2;

    sqRet.push_back(s1);

    CubeletPosition cp_from(fp_from.all());
    if(s1.f != undefside)
        for(std::size_t c = 0; c < s1.no_of_turns; c++)
            cp_from *= (s1.is_clockwise ? s1.f : opposite(s1.f) );

    if(cp_from == CubeletPosition(front,up,left) || cp_from == CubeletPosition(front,left))
        s2 = Step(front,false);
    else if(cp_from == CubeletPosition(front,up,right) || cp_from == CubeletPosition(front,up))
        s2 = Step(front,false,2);
    else if(cp_from == CubeletPosition(front,right,down) || cp_from == CubeletPosition(front,right))
        s2 = Step(front);

    sqRet.push_back(s2);

    return sqRet;

}

StepSequence Primitive::getSequence(FaceletPosition P_start, FaceletPosition P_end)
{

    StepSequence ret;

    CubeletPosition cp_start(P_start.all());
    CubeletPosition cp_should;

    if(P_start.ptype() == corner)
        cp_should = CubeletPosition(down,back,left);
    else if(P_start.ptype() == edge)
        cp_should = CubeletPosition(down,back);

    ///1. Get step seq required to bring destination position to standard position.
    ///Bring all positions to standard orientation. (rotation of whole Cube).
    ///P_end --> standard position
    StepSequence ssStd = getSeqToStandard(P_end);
    for(const auto& s: ssStd)
        if(s.f != undefside)
            for(std::size_t c = 0; c < s.no_of_turns; c++)
            {
                P_start *= (s.is_clockwise ? s.f : opposite(s.f) );
                P_end *= (s.is_clockwise ? s.f : opposite(s.f) );
                cp_start *= (s.is_clockwise ? s.f : opposite(s.f) );
            }

    ///2. Bring P_start position, from where Cubelet is to be moved to new position, to pre-specified position
    ///from where steps required to move Cubelet to P_end are well defined. (rotation of Face)
    ///P_start --> predefined position
    Relation key_t(P_start, P_end);
    const auto itRelStep = mRelStep.find(key_t);
    if(itRelStep == mRelStep.end()){
        CletRelation ckey( cp_start, cp_should );
        ret = mCletStep[ ckey ];
    }

    ///3. Finally move P_start to P_end (rotation fo Face)
    Position p_new = P_start.result(ret).all();
    FaceletPosition fp_new( p_new.all() );

    Relation key( fp_new, P_end);
    auto seq = mRelStep[key];
    ret.splice(ret.end(), seq );

    ///4. Result cann't be returned as such. we have to nullify the effect of step #1 i.e. roatate in reverse
    ///sequence to get to original view. (rotation of whole Cube)
    StepSequence rsStd = getRotationalReverseSeq(ssStd);
    for(const auto& rs: rsStd)
        for(auto& s: ret)
            if(rs.f != undefside && s.f != undefside)
                for(std::size_t c = 0; c < rs.no_of_turns; c++)
                    s.f *= (rs.is_clockwise ? rs.f : opposite(rs.f) );


    return ret;

}

StepSequence Primitive::getRotationalReverseSeq(StepSequence seq)
{
    StepSequence rev;
    for(auto rit = seq.rbegin(); rit != seq.rend(); rit++)
    {
        Step s(*rit);
        s.is_clockwise = s.is_clockwise?false:true;
        rev.push_back(s);
    }
    return rev;
}





//===================== Query ========================

