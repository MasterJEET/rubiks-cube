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
    std::string fac1,fac2,col;
    is >> fac1 >> col;
    
}
