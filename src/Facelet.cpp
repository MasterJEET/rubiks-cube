/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "Facelet.h"

Facelet::Facelet(const Color * const col, const FaceSide *side): col(col), side(side){
    //Nothing for now
}

const Color * const Facelet::getColor(){
    return col;
}

const FaceSide * const Facelet::getFaceSide(){
    return side;
}

void Facelet::setFaceSide(const FaceSide *const side){
    this->side = side;
}

std::ostream& operator<<(std::ostream& os, Facelet F){
    return os << "Facelet: col = " << *F.getColor() << ", *side = " << *F.getFaceSide();
}

