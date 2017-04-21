/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "Cubelet.h"

Cubelet::Cubelet(Position &pos, Facelet *fac1): ppos(&pos), vecFac{fac1}{
    //Nothing for now
}

Cubelet::Cubelet(Position &pos, Facelet *fac1, Facelet *fac2): ppos(&pos), vecFac{fac1, fac2}{
    //Nothing for now
}

Cubelet::Cubelet(Position &pos, Facelet *fac1, Facelet *fac2, Facelet *fac3): ppos(&pos), vecFac{fac1, fac2, fac3}{
    //Nothing for now
}

const std::vector<Facelet*> *Cubelet::getFacelet(){
    return &vecFac;
};

const Position *Cubelet::getPosition(){
    return ppos;
};

void Cubelet::setPosition(Position *ppos){
    this->ppos = ppos;
}

std::ostream& operator<<(std::ostream& os, Cubelet C){
    os << "Colors: { ";
    for(auto it: *C.getFacelet())
        os << *it->getColor() << " ";
    os << "} ";
    os << *C.getPosition();
    return os;
};

