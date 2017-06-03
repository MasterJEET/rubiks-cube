/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "Facelet.h"

/*Facelet::Facelet(Color col): Facelet(col, nullptr){
    //Nothing for now
}*/

Facelet::Facelet(Color &col, FaceSide &fac): col(col), fac(&fac){
    //Nothing for now
}

/*Facelet::Facelet(Color col, FaceSide *fac): col(col), fac(fac){
    //Nothing for now
}*/

const Color *Facelet::getColor(){
    return &col;
}

const FaceSide *Facelet::getFaceSide(){
    return fac;
}

void Facelet::setFaceSide(FaceSide *fac){
    this->fac = fac;
}

std::ostream& operator<<(std::ostream& os, Facelet F){
    return os << "Facelet: col = " << *F.getColor() << ", *fac = " << *F.getFaceSide();
}

