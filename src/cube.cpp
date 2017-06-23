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

    mapFaceletFace mFaceletFace;
    std::string strCtrFaceSide, strCtrColor;
    FaceSide ctrSide;
    Color ctrCol;

    //Get FaceSide and Color for Center Facelet
    is >> strCtrFaceSide >> strCtrColor;
    ctrSide = FaceSideFromLetter(strCtrFaceSide);
    ctrCol = ColorFromLetter(strCtrColor);
    
    //Create Center Facelet and add it to map
    Facelet ctrFac( ctrCol, ctrSide );
    pairFaceSide pSide(ctrSide, F_UNDEFINED);
    mFaceletFace.insert( std::pair<pairFaceSide, Facelet>( pSide, ctrFac  ) );

    mFaceletAll.insert( std::pair<FaceSide, mapFaceletFace>(ctrSide, mFaceletFace) );

};


Facelet& Cube::getFacelet(FaceSide fside1, FaceSide fside2, FaceSide fside3) const{
    if( fside1 == F_UNDEFINED ){
        std::string error_msg = std::string() + "First argument of " + __func__+": Cannot be F_UNDEFINED...\n";
        error_msg += std::string() + "See \"" + std::getenv("CUBE_HOME") + "/inc/FaceSide.def\" for valid values...\n";
        throw std::invalid_argument(error_msg);
    }
    mapFaceletFace mFaceletFace = mFaceletAll.at(fside1);
    pairFaceSide pSide;
    
    if(fside2 == F_UNDEFINED && fside3 == F_UNDEFINED)
        pSide = pairFaceSide(fside1, fside2);
    else
        pSide = pairFaceSide(fside2, fside3);
        
    mFaceletFace.at(pSide);
    return mFaceletFace.at(pSide);
};

