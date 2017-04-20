/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "Face.h"
/*
Face::Face(){
    //Nothing for now
}*/

Face::Face(std::istream &is){
    std::string strfs1,strfs2,scol;
    createmapColor();
    createmapFaceSide();
    //Center FaceSide
    is >> strfs1 >> scol;
    if(FaceSideFromStr(strfs1)==F_UNDEFINED)
        ~Face();
    fs = FaceSideFromStr(strfs1);
    FaceSide cfac = FaceSideFromStr(strfs1);
    FaceSide ufac =  F_UNDEFINED;
    Facelet val = Facelet( ColorFromStr(scol), fs);
    mpair key = mpair(cfac, ufac);
    mFace.insert( std::pair<mpair, Facelet>(key, val) );
    
}

Facelet *Face::getFacelet(std::string sfac1, std::string sfac2){
    //Nothing for now
};

void Face::addToMap(std::string sfac1,  std::string scol){
    //Color col = ColorFromStr();
    //Facelet val = Facelet(ColorFromStr())
};
