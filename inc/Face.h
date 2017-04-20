/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#ifndef FACE_H
#define FACE_H

#include "Facelet.h"
#include <map>
#include <istream>

typedef std::map<std::pair<FaceSide, FaceSide>, Facelet> mapFacelet;

class Face{
    private:
        const FaceSide fs;
        mapFacelet mFace;
    public:
        Face(FaceSide &fs);
        Face(FaceSide &fs, std::istream &is);
};

#endif
