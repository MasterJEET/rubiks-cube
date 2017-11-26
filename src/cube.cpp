/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#include "cube.h"

Cube::Cube(std::istream &is){

    //Get all Faces
    for(int i=0; i<6; i++)
        createFace(is);


    //Create Cubelets from arrFacelet and store it in Cubelet array
    createCube();
};

void Cube::createFace(std::istream &is ){

    std::string strFaceSide, strFaceSide2, strColor;
    FaceSide ctrSide, edgeSide, corSide;
    Color col;

    //Get FaceSide and Color for Center Facelet
    is >> strFaceSide >> strColor;
    ctrSide = FaceSideFromLetter(strFaceSide);
    col = ColorFromLetter(strColor);

    //Create Center Facelet and add it to array
    aFacelet[ FaceletPosition(ctrSide) ] = Facelet(col, ctrSide);

    //Get FaceSide and Color for Edge Facelets and add them to array
    for(size_t i=0; i<4; i++){
        is >> strFaceSide >> strColor;
        edgeSide = FaceSideFromLetter(strFaceSide);
        col = ColorFromLetter(strColor);
        FaceletPosition fp(ctrSide, edgeSide);
        aFacelet[ fp ] = Facelet(col, fp);
    }

    //Get FaceSide and Color for Corner Facelets and add them to array
    for(size_t i=0; i<4; i++){
        is >> strFaceSide >> strFaceSide2 >> strColor;
        edgeSide = FaceSideFromLetter(strFaceSide);
        corSide = FaceSideFromLetter(strFaceSide2);
        col = ColorFromLetter(strColor);
        FaceletPosition fp(ctrSide, edgeSide, corSide);
        aFacelet[ fp ] = Facelet(col, fp);
    }


};

void Cube::createCube(){
   
    //Vector of all valid FaceSides
    std::vector<FaceSide> vSingleFS = {
        {front} , {back} , {up} , {down} , {right} , {left}
    };

    //Create center Cubelets and add to array
    for( const auto& vfs: vSingleFS ){
        FaceletPosition fp(vfs);
        CubeletPosition cp(vfs);
        aCubelet[ cp ] = Cubelet( aFacelet[fp] );
    }


    //Vector of vector of pair FaceSides
    std::vector< std::vector<FaceSide> > vDoubleFS = { 
                                        { front, up }, { front, right }, { front, down }, { front, left },
                                        { up, right }, { down, right }, { down, left }, { up, left },
                                        { back, up }, { back, right }, { back, down }, { back, left }
                                      };

    for( const auto& vfs: vDoubleFS ){
        FaceletPosition fp1(vfs);
        FaceletPosition fp2(vfs[1], vfs[0]);
        CubeletPosition cp(vfs);
        aCubelet[ cp ] = Cubelet( aFacelet[fp1], aFacelet[fp2] );
    }

    //Vector of vector of triple FaceSides
    std::vector< std::vector<FaceSide> > vTripleFS = { { front, right, up}, { back, right, up }, { back, left, up}, { front, left, up },
                                                       { front, right, down}, { back, right, down }, { back, left, down}, { front, left, down } };

    for( const auto& vfs: vTripleFS ){
        FaceletPosition fp1(vfs);
        FaceletPosition fp2(vfs[1], vfs[0], vfs[2]);
        FaceletPosition fp3(vfs[2], vfs[0], vfs[1]);
        CubeletPosition cp(vfs);
        aCubelet[ cp ] = Cubelet( aFacelet[fp1], aFacelet[fp2], aFacelet[fp3] );
    }
}

void Cube::show(const FaceSide& f){
    auto tlist = getFaceletPosition(f);
    auto it = tlist.begin();
    while( it != tlist.end()){
        for(int i=0;i<3;i++,it++){
            Color c = getFacelet(*it).getColor();
            std::cout << colorFormat(c) << " " ;
        }
        std::cout << std::endl;
    }
}


void Cube::rotateLayer(const FaceSide& f, bool is_clockwise , bool is_mid){

    //edge ( center if is_mid is true ) positions to operate on
    vecCletPos ve;
    //corner ( mid edge if is_mid is true ) positions to operate on
    vecCletPos vc;

    if(is_mid){
        ve = vecCenterEquivalence<CubeletPosition>(f);
        vc = vecMidEdgeEquivalence<CubeletPosition>(f);
    }else{
        ve = vecEdgeEquivalence<CubeletPosition>(f);
        vc = vecCornerEquivalence<CubeletPosition>(f);
    };


    for(const auto& v:{ve,vc}){
        //Updating Cubelets at required position
        for(const auto& p:v)
            aCubelet[p] *= (is_clockwise?f:opposite(f));
        //Relocating Cubelets to updated position
        std::size_t u = *v.begin();
        std::size_t r = *(v.begin()+1);
        std::size_t d = *(v.begin()+2);
        std::size_t l = *(v.begin()+3);
        std::swap(aCubelet[u], aCubelet[r]);
        if(is_clockwise){
            std::swap(aCubelet[l], aCubelet[u]);
            std::swap(aCubelet[d], aCubelet[l]);
        }else{
            std::swap(aCubelet[d], aCubelet[r]);
            std::swap(aCubelet[l], aCubelet[d]);
        }
    }

}

void Cube::rotateSide(const FaceSide& f, bool is_clockwise ){
    rotateLayer(f,is_clockwise);
}

void Cube::rotateMid(const FaceSide& f, bool is_clockwise){
    rotateLayer(f,is_clockwise,true);
}


void Cube::rotate(const FaceSide& f,bool is_clockwise){
    FaceSide b = opposite(f);

    //rotate front  equivalent (i.e. given ) Face
    rotateSide(f,is_clockwise);
    //rotate back equivalent (i.e. opposite of given) Face in the same absolute sense as in case of 'up equivalence'
    rotateSide(b,!is_clockwise);
    //rotate mid equivalent layer
    rotateMid(f,is_clockwise);
}



listFletPos getFaceletPosition(const FaceSide f){
    listFletPos tlist;
    FaceSide u,r,d,l;

    setEquivalentFaceSide(f,u,r,d,l);


    tlist.push_back({ f,l,u }); tlist.push_back({ f,u });   tlist.push_back({ f,r,u });
    tlist.push_back({ f,l });   tlist.push_back(f);         tlist.push_back({ f,r });
    tlist.push_back({ f,l,d }); tlist.push_back({ f,d });   tlist.push_back({ f,r,d });

    return tlist;
}


template <typename P>
std::vector<P> vecEdgeEquivalence(const FaceSide& f){

    FaceSide u,r,d,l;
    setEquivalentFaceSide(f,u,r,d,l);

    std::vector<P>   vpos;
    vpos.push_back( P(f,u) );
    vpos.push_back( P(f,r) );
    vpos.push_back( P(f,d) );
    vpos.push_back( P(f,l) );

    return vpos;
}

template std::vector<CubeletPosition> vecEdgeEquivalence<CubeletPosition>(const FaceSide& f);
template std::vector<FaceletPosition> vecEdgeEquivalence<FaceletPosition>(const FaceSide& f);


template <typename P>
std::vector<P> vecCornerEquivalence(const FaceSide& f){
    FaceSide u,r,d,l;
    setEquivalentFaceSide(f,u,r,d,l);

    std::vector<P>    vpos;
    vpos.push_back( P(f,u,l) );
    vpos.push_back( P(f,u,r) );
    vpos.push_back( P(f,d,r) );
    vpos.push_back( P(f,d,l) );

    return vpos;
}

template std::vector<CubeletPosition> vecCornerEquivalence<CubeletPosition>(const FaceSide& f);
template std::vector<FaceletPosition> vecCornerEquivalence<FaceletPosition>(const FaceSide& f);


template <typename P>
std::vector<P> vecCenterEquivalence(const FaceSide& f){
    FaceSide u,r,d,l;
    setEquivalentFaceSide(f,u,r,d,l);

    std::vector<P>    vpos;
    vpos.push_back( P(u) );
    vpos.push_back( P(r) );
    vpos.push_back( P(d) );
    vpos.push_back( P(l) );

    return vpos;

}


template <typename P>
std::vector<P> vecMidEdgeEquivalence(const FaceSide& f){
    FaceSide u,r,d,l;
    setEquivalentFaceSide(f,u,r,d,l);

    std::vector<P>    vpos;
    vpos.push_back( P(u,l) );
    vpos.push_back( P(u,r) );
    vpos.push_back( P(d,r) );
    vpos.push_back( P(d,l) );

    return vpos;
}
