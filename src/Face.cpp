/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "Face.h"
#include <stdexcept>
#include <iostream>
/*
Face::Face(){
    //Nothing for now
}*/

Face::Face(std::istream &is){
    std::string sfac0,sfac1,sfac2,scol;
    createmapColor();
    createmapFaceSide();

    //Center FaceSide
    is >> sfac0 >> scol;
    fs = FaceSideFromStr(sfac0);
    addToMap(sfac0, sfac0, scol);

    //Edge 1-4
    for(size_t i = 0; i<4; i++){
        is >> sfac2 >> scol;
        addToMap(sfac0, sfac2, scol);
    }

    //Corner 1-4
    for(size_t i = 0; i<4; i++){
        is >> sfac1 >> sfac2 >> scol;
        addToMap(sfac1, sfac2, scol);
    }
}

void Face::addToMap(std::string sfac1, std::string sfac2, std::string scol){
    FaceSide fac1 = FaceSideFromStr(sfac1);
    FaceSide fac2 = FaceSideFromStr(sfac2);
    mFacePair key = mFacePair(fac1, fac2);
    Color col = ColorFromStr(scol);
    Facelet val = Facelet( col, fs);
    mFace.insert( std::pair<mFacePair, Facelet>(key, val) );
};

Facelet *Face::getFacelet(std::string sfac1, std::string sfac2){
    FaceSide fac1 = FaceSideFromStr(sfac1);
    FaceSide fac2 = FaceSideFromStr(sfac2);
    mFacePair key = mFacePair(fac1, fac2);
    return &mFace.at(key);
};

void Face::printAllFacelet(){
    for(auto& it: mFace)
        std::cout << "(" << it.first.first << ", " << it.first.second << ")" << " --> " << *it.second.getColor() << std::endl;
};
