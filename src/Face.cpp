/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "Face.h"

Face::Face(FaceSide &fs): fs(fs){
    //Nothing for now
}

Face::Face(FaceSide &fs, std::istream &is): fs(fs){
    std::string strfs1,strfs2,col;
    createmapColor();
    createmapFaceSide();
    //Center FaceSide
    is >> strfs1 >> col;
    FaceSide cfac = FaceSideFromStr(strfs1);
    Facelet fl = Facelet( ColorFromStr(col), fs);
    mFace.insert( std::pair<FaceSide,FaceSide>(cfac, F_UNDEFINED), fl );
    
}
