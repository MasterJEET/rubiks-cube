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

    //Create Cubelets from mapFacelet and store it in map
    createCubelet();
};

void Cube::createFace(std::istream &is){

    std::string strFaceSide, strFaceSide2, strColor;
    FaceSide ctrSide, edgeSide, corSide;
    Color col;

    //Get FaceSide and Color for Center Facelet
    is >> strFaceSide >> strColor;
    ctrSide = FaceSideFromLetter(strFaceSide);
    col = ColorFromLetter(strColor);

    //Create Center Facelet and add it to map
    mFacelet[ Position(ctrSide) ] = Facelet(col, ctrSide);

    //Get FaceSide and Color for Edge Facelets and add them to map
    for(size_t i=0; i<4; i++){
        is >> strFaceSide >> strColor;
        edgeSide = FaceSideFromLetter(strFaceSide);
        col = ColorFromLetter(strColor);
        mFacelet[ Position(ctrSide, edgeSide) ] = Facelet(col, ctrSide);
    }

    //Get FaceSide and Color for Corner Facelets and add them to map
    for(size_t i=0; i<4; i++){
        is >> strFaceSide >> strFaceSide2 >> strColor;
        edgeSide = FaceSideFromLetter(strFaceSide);
        corSide = FaceSideFromLetter(strFaceSide2);
        col = ColorFromLetter(strColor);
        mFacelet[ Position(ctrSide, edgeSide, corSide) ] = Facelet(col, ctrSide);
    }


};


Facelet Cube::getFacelet(const FaceSide fside1, const FaceSide fside2, const FaceSide fside3) const{
    return mFacelet.at( Position (fside1, fside2, fside3));
};

Facelet Cube::getFacelet(const FaceSide fside1, const FaceSide fside2) const{
    return mFacelet.at( Position (fside1, fside2));
};

Facelet Cube::getFacelet(const FaceSide fside1) const{
    return mFacelet.at( Position (fside1));
};

Facelet Cube::getFacelet(const Position pos) const{
    return mFacelet.at( pos );
};

void Cube::createCubelet(){
   
    //Vector of all valid FaceSides
    std::vector<FaceSide> vSingleFS = {front, back, up, down, right, left};

    //Create center Facelets and add to map
    for( const auto& fs: vSingleFS ){
        //Facelet* pFL = &mFacelet[ fs ];
        mCubelet[ fs ] = &mFacelet[ fs ];
    }

    //Vector of vector of pair FaceSides
    std::vector< std::vector<FaceSide> > vDoubleFS = { 
                                        { front, up }, { front, right }, { front, down }, { front, left },
                                        { up, right }, { down, right }, { down, left }, { up, left },
                                        { back, up }, { back, right }, { back, down }, { back, left }
                                      };


    //Vector of vector of triple FaceSides
    std::vector< std::vector<FaceSide> > vTripleFS = { { front, right, up}, { back, right, up }, { back, left, up}, { front, left, up },
                                                       { front, right, down}, { back, right, down }, { back, left, down}, { front, left, down } };
}

Cubelet Cube::getCubelet(const Position pos) const{
    return mCubelet.at( pos );
}
