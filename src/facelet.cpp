/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "facelet.h"

Facelet::Facelet(const Color _col, const FaceSide _side): col(_col), side(_side){
    //Nothing for now
}

Facelet::Facelet(const FaceSide _side, const Color _col): Facelet(_col, _side){
    //Nothing for now
}

const Color Facelet::getColor() const{
    return col;
}

const FaceSide Facelet::getFaceSide() const{
    return side;
}

void Facelet::setFaceSide(const FaceSide _side){
    side = _side;
}

std::ostream& operator<<(std::ostream& os, Facelet F){
    return os << "Facelet: col = " << F.getColor() << ", side = " << F.getFaceSide();
}

