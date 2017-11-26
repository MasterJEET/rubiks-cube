/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#include "cube.h"

Cube::Cube(std::istream &is){

    ///Get all Faces
    for(int i=0; i<6; i++)
        createFace(is);


    ///Create Cubelets from arrFacelet and store it in map
    createCube();
};

void Cube::createFace(std::istream &is ){

    std::string strFaceSide, strFaceSide2, strColor;
    FaceSide ctrSide, edgeSide, corSide;
    Color col;

    ///Get FaceSide and Color for Center Facelet
    is >> strFaceSide >> strColor;
    ctrSide = FaceSideFromLetter(strFaceSide);
    col = ColorFromLetter(strColor);

    ///Create Center Facelet and add it to map
    aFacelet[ FaceletPosition(ctrSide) ] = Facelet(col, ctrSide);

    ///Get FaceSide and Color for Edge Facelets and add them to map
    for(size_t i=0; i<4; i++){
        is >> strFaceSide >> strColor;
        edgeSide = FaceSideFromLetter(strFaceSide);
        col = ColorFromLetter(strColor);
        FaceletPosition fp(ctrSide, edgeSide);
        aFacelet[ fp ] = Facelet(col, fp);
    }

    ///Get FaceSide and Color for Corner Facelets and add them to map
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
   
    ///Vector of all valid FaceSides
    std::vector<FaceSide> vSingleFS = {
        {front} , {back} , {up} , {down} , {right} , {left}
    };

    ///Create center Cubelets and add to map
    for( const auto& vfs: vSingleFS ){
        FaceletPosition fp(vfs);
        CubeletPosition cp(vfs);
        aCubelet[ cp ] = Cubelet( aFacelet[fp] );
    }


    ///Vector of vector of pair FaceSides
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

    ///Vector of vector of triple FaceSides
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



/*! Fetch list of FaceletPositions associated with a given FaceSide
 *
 *                U U U
 *                U U U
 *                U U U
 *          B B B L L L F F F R R R      1 2 3 #
 *          B B B L L L F F F R R R      4 5 6 # This is the sequence
 *          B B B L L L F F F R R R      7 8 9 #
 *                D D D
 *                D D D
 *                D D D
 * Returns above positions for a face,
 * Order of positions in the list is depicted by above diagram
 *
 * */

std::list<FaceletPosition> Cube::getFaceletPosition(const FaceSide f){
    std::list<FaceletPosition> tlist;
    FaceSide u,r,d,l;

    setEquivalentFaceSide(f,u,r,d,l);


    tlist.push_back({ f,l,u }); tlist.push_back({ f,u });   tlist.push_back({ f,r,u });
    tlist.push_back({ f,l });   tlist.push_back(f);         tlist.push_back({ f,r });
    tlist.push_back({ f,l,d }); tlist.push_back({ f,d });   tlist.push_back({ f,r,d });

    return tlist;
}


void Cube::rotateLayer(const FaceSide& f, bool is_clockwise , bool is_mid){

    //edge (or center) positions to operate on
    vecCletPos ve;
    // corner (or mid edge) positions to operate on
    vecCletPos vc;

    if(is_mid){
        ve = vecCenterEquPosition(f);
        vc = vecMidEdgeEquPosition(f);
    }else{
        ve = vecEdgeEquPosition(f);
        vc = vecCornerEquPosition(f);
    };


    for(const auto& v:{ve,vc}){
        //Updating Cubelets at required position
        for(const auto& p:v)
            aCubelet[p] *= (is_clockwise?f:opposite(f));
        //Updating indices i.e. relocating Cubelets to updated position
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


/**
 * Let 1 & 2 denotes the state of Cube before & after the operation. With usual notation of
 * - F: Front
 * - B: Back
 * - U: Up
 * - D: Down
 * - L: Left
 * - R: Right
 *
 * If operated with FaceSide Up on Cube with clockwise set to true, Up and Down Faces remain at their place.
 * Front FaceSide turns to Left, Left turns to Back and so on.
 * - 1U -> 2U
 * - 1D -> 2D
 * - 1F -> 2L
 * - 1R -> 2F
 * - 1B -> 2R
 * - 1L -> 2B
 *
 */
void Cube::rotate(const FaceSide& f,bool is_clockwise){
    FaceSide u, r, d, l;
    setEquivalentFaceSide(f,u,r,d,l);

    //rotate up equivalent FaceSide
    rotateSide(u,is_clockwise);
    //rotate down equivalent FaceSide in the same absolute sense as in case of 'up equivalence'
    rotateSide(d,!is_clockwise);
    //rotate mid equivalent layer
    rotateMid(u,is_clockwise);
};
