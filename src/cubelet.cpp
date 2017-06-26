/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "cubelet.h"

Cubelet::Cubelet(){};

Cubelet::Cubelet(const Facelet fac1):vecFac{fac1}{
    pos = Position(fac1.getFaceSide());
}

Cubelet::Cubelet(const Facelet fac1, const Facelet fac2):vecFac{fac1, fac2}{
    pos = Position(fac1.getFaceSide(), fac2.getFaceSide());
}

Cubelet::Cubelet(const Facelet fac1, const Facelet fac2, const Facelet fac3):vecFac{fac1, fac2, fac3}{
    pos = Position(fac1.getFaceSide(), fac2.getFaceSide(), fac3.getFaceSide());
}

const std::vector<Facelet> * Cubelet::getFacelet() const{
    return &vecFac;
}

Facelet Cubelet::getFaceletAt(size_t index) const {
    return vecFac.at(index);
}

Position Cubelet::getPosition() const{
    return pos;
}

void Cubelet::setPosition(const Position _pos){
    pos = _pos;
}

std::ostream& operator<<(std::ostream& os, Cubelet C){
    os << "Colors: { ";
    for(auto it: *C.getFacelet())
        os << it.getColor() << " ";
    os << "} ";
    os << C.getPosition();
    return os;
}