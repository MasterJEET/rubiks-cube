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

typedef std::pair<FaceSide&,FaceSide> mpair;
typedef std::map<mpair, Facelet> mapFacelet;

class Face{
    private:
        const FaceSide fs;
        mapFacelet mFace;
    public:
        //Face();
        Face(std::istream &is);
        void addToMap(std::string sfac1, std::string col);
        Facelet *getFacelet(std::string sfac1, std::string sfac2);
};

#endif
