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

    std::string strCtrFaceSide, strCtrColor;
    FaceSide ctrSide;
    Color ctrCol;

    //Get FaceSide and Color for Center Facelet
    is >> strCtrFaceSide >> strCtrColor;
    ctrSide = FaceSideFromLetter(strCtrFaceSide);
    ctrCol = ColorFromLetter(strCtrColor);

    //Create Center Facelet and add it to map
    Facelet ctrFac( ctrCol, ctrSide );
    Position ctrP( ctrSide );

    mFacelet[ ctrP ] = ctrFac;


};


Facelet Cube::getFacelet(FaceSide fside1, FaceSide fside2, FaceSide fside3) const{
    Position pos(fside1);
    return mFacelet.at( pos );
};

