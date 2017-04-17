/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "Cubelet.h"

Cubelet::Cubelet(Position &pos, Facelet fac1): ppos(&pos), vecFac{fac1}{
    //Nothing for now
}

const std::vector<Facelet> *Cubelet::getFacelet(){
    return &vecFac;
};

const Position *Cubelet::getPosition(){
    return ppos;
};

void Cubelet::setPosition(Position *ppos){
    this->ppos = ppos;
}

std::ostream& operator<<(std::ostream& os, Cubelet C){
    return os << *C.getPosition();
};

