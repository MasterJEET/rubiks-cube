/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "Cubelet.h"
/*
Cubelet::Cubelet(const Position * const ppos, Facelet * const fac1): ppos(ppos), vecFac{fac1}{
    //Nothing for now
}
*/
Cubelet::Cubelet(Facelet * const fac1):vecFac{fac1}{
    Position pos(fac1->getFaceSide());
    ppos = &pos;
}

Cubelet::Cubelet(const Position * const ppos, Facelet * const fac1, Facelet * const fac2): ppos(ppos), vecFac{fac1, fac2}{
    //Nothing for now
}

Cubelet::Cubelet(const Position * const ppos, Facelet * const fac1, Facelet * const fac2, Facelet * const fac3): ppos(ppos), vecFac{fac1, fac2, fac3}{
    //Nothing for now
}

const std::vector<Facelet *> * const Cubelet::getFacelet(){
    return &vecFac;
};

const Position * const Cubelet::getPosition(){
    return ppos;
};

void Cubelet::setPosition(const Position * const ppos){
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
