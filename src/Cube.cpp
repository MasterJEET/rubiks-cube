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
    getFace(is);
};

void Cube::getFace(std::istream &is){
    mapFacelet mFac;

    std::string strFaceSide, strColor;
    //Getting FaceSide and Color for Center Facelet
    is >> strFaceSide >> strColor;
    std::cout << "FaceSide: " << strFaceSide << ", Color: " << strColor << std::endl;
    //Creating Center Facelet
    Facelet cFac( ColorFromStr(strColor), FaceSideFromStr(strFaceSide) );
};
