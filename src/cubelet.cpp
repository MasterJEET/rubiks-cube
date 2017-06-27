/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "cubelet.h"

Cubelet::Cubelet(Facelet* p_fac1):vecFac{p_fac1}{
    pos = Position(p_fac1->getFaceSide());
}

Cubelet::Cubelet(Facelet* p_fac1, Facelet* p_fac2):vecFac{p_fac1, p_fac2}{
    pos = Position(p_fac1->getFaceSide(), p_fac2->getFaceSide());
}

Cubelet::Cubelet(Facelet* p_fac1, Facelet* p_fac2, Facelet* p_fac3):vecFac{p_fac1, p_fac2, p_fac3}{
    pos = Position(p_fac1->getFaceSide(), p_fac2->getFaceSide(), p_fac3->getFaceSide());
}

std::ostream& operator<<(std::ostream& os, Cubelet C){
    os << "Colors: { ";
    for(auto it: C.vecFac)
        os << it->getColor() << " ";
    os << "} ";
    os << C.pos;
    return os;
}

bool operator==(const Cubelet& lhs, const Cubelet& rhs){
    if( !(lhs.pos == rhs.pos) )
        return false;

    if(lhs.vecFac.size() != rhs.vecFac.size())
        return false;

    for(size_t i=0; i < lhs.vecFac.size() ; i++)
        if( !(*lhs.vecFac[i] == *rhs.vecFac[i]) )
            return false;

    return true;
}

bool operator!=(const Cubelet& lhs, const Cubelet&rhs){
    return !(lhs == rhs);
}
