/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#include "Cube.h"

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
    std::cout << "FaceSide: " << strCtrFaceSide << ", Color: " << strCtrColor << std::endl;
    ctrSide = FaceSideFromStr(strCtrFaceSide);
    ctrCol = ColorFromStr(strCtrColor);
    
    //Create Center Facelet and add it to map
    Facelet ctrFac( ctrCol, ctrSide );
    pairFaceSide pSide(ctrSide, F_UNDEFINED);
    mFaceletFace.insert( std::pair<pairFaceSide, Facelet>( pSide, ctrFac  ) );

    mFaceletAll.insert( std::pair<FaceSide, mapFaceletFace>(ctrSide, mFaceletFace) );

    //const Facelet& flet = getFacelet(ctrSide, F_UNDEFINED, F_UNDEFINED);
    
};

/*
Facelet& Cube::getFacelet(FaceSide fside1, FaceSide fside2, FaceSide fside3) const{
    mapFaceletFace mFaceletFace = mFaceletAll.at(fside1);
    pairFaceSide pSide(fside2, fside3);
    return mFaceletFace.at(pSide);
};
*/
