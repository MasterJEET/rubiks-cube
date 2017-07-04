/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "cubelet.h"

Cubelet::Cubelet(Facelet fac1):vecFac{fac1}{
    pos = CubeletPosition(fac1.side());
}

Cubelet::Cubelet(Facelet fac1, Facelet fac2):vecFac{fac1, fac2}{
    pos = CubeletPosition(fac1.side(), fac2.side());
}

Cubelet::Cubelet(Facelet fac1, Facelet fac2, Facelet fac3):vecFac{fac1, fac2, fac3}{
    pos = CubeletPosition(fac1.side(), fac2.side(), fac3.side());
}

Cubelet::Cubelet(std::vector<Facelet> _vecFac): vecFac(_vecFac) {
    switch( _vecFac.size() ){
        case 1:
            pos = CubeletPosition(_vecFac[0].side() );
            break;
        case 2:
            pos = CubeletPosition( std::vector<FaceSide>{  _vecFac[0].side(), _vecFac[1].side()   }  );
            break;
        case 3:
            pos = CubeletPosition( std::vector<FaceSide>{  _vecFac[0].side(),  _vecFac[1].side(),  _vecFac[2].side()   }  );
            break;
        default:
            throw std::runtime_error(std::string() + __func__ + ": _vecFac can only have size such that 0 < size <= 3...");
            
    }
}

std::ostream& operator<<(std::ostream& os, Cubelet C){
    os << "Colors: { ";
    for(auto it: C.vecFac)
        os << it.getColor() << " ";
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
        if( !(lhs.vecFac[i] == rhs.vecFac[i]) )
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
