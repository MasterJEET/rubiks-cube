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

Cubelet::Cubelet(FaceletPosition cp1): vecFP{cp1} {
    
};

std::ostream& operator<<(std::ostream& os, Cubelet C){
    os << "Colors: { ";
    for(auto it: C.vecFac)
        os << it->getColor() << " ";
    os << "} ";
    os << C.pos;
    return os;
}

bool operator==(const Cubelet& lhs, const Cubelet& rhs){
    if( lhs.pos != rhs.pos)
        return false;

    if(lhs.vecFac.size() != rhs.vecFac.size())
        return false;

    for(size_t i=0; i < lhs.vecFac.size() ; i++)
        if( !(*lhs.vecFac[i] == *rhs.vecFac[i]) )
            return false;

    return true;
}


//Equality
bool operator==(const CubeletPosition& lhs, const CubeletPosition& rhs){
   //sorting FaceSides of lhs
   FaceSide lfs0 = lhs.getSideAt(0);
   FaceSide lfs1 = lhs.getSideAt(1);
   FaceSide lfs2 = lhs.getSideAt(2);

   if( lfs0 > lfs1 )
       std::swap(lfs0, lfs1);
   if( lfs1 > lfs2 )
       std::swap(lfs1, lfs2);
   if( lfs0 > lfs1 )
       std::swap(lfs0, lfs1);
   //sorting FaceSides of rhs
   FaceSide rfs0 = rhs.getSideAt(0);
   FaceSide rfs1 = rhs.getSideAt(1);
   FaceSide rfs2 = rhs.getSideAt(2);

   if( rfs0 > rfs1 )
       std::swap(rfs0, rfs1);
   if( rfs1 > rfs2 )
       std::swap(rfs1, rfs2);
   if( rfs0 > rfs1 )
       std::swap(rfs0, rfs1);

   if( lfs0 != rfs0 || lfs1 != rfs1 || lfs2 != rfs2 )
       return false;

   return true;

};
