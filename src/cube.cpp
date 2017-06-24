/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#include "cube.h"

Cube::Cube(){
    //Nothing here for now
};

Cube::Cube(std::istream &is){
    createFace(is);
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


Facelet Cube::getFacelet(FaceSide fside1, FaceSide fside2, FaceSide fside3) const{
    return mFacelet.at( Position (fside1, fside2, fside3));
};

