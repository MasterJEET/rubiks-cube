/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "cubelet.h"


std::ostream& operator<<(std::ostream& os, CubeletPosition CP){
    return os << Position(CP.vecSide);
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


Cubelet::Cubelet(std::vector<Facelet> _vecFac): vFacelet(_vecFac) {
    switch( _vecFac.size() ){
        case 1:
            {
            pos = CubeletPosition( _vecFac[0].getPosition() );
            break;
            }
        case 2:
            {
            CubeletPosition cp1(_vecFac[0].getPosition());
            CubeletPosition cp2(_vecFac[1].getPosition());
            if(cp1 != cp2)
                throw std::runtime_error(std::string() + __func__ + ": Two Facelets provided doesnot belong to same Cubelet");
            pos = cp1 ;
            break;
            }
        case 3:
            {
            CubeletPosition cp1(_vecFac[0].getPosition());
            CubeletPosition cp2(_vecFac[1].getPosition());
            CubeletPosition cp3(_vecFac[2].getPosition());
            if(cp1 != cp2 || cp1 != cp3 || cp2 != cp3)
                throw std::runtime_error(std::string() + __func__ + ": Three Facelets provided doesnot belong to same Cubelet");
            pos = cp1;
            break;
            }
        default:
            throw std::runtime_error(std::string() + __func__ + ": _vecFac can only have size such that 0 < size <= 3...");
            
    }
}

listFaceletPosition Cubelet::getFaceletPositionList() const{
    listFaceletPosition lFaceletPosition;

    if(pos.size() == 1)
        lFaceletPosition.push_back( pos.getSideAt(0) );

    if(pos.size() == 2){
        lFaceletPosition.push_back({ pos.getSideAt(0), pos.getSideAt(1) });
        lFaceletPosition.push_back({ pos.getSideAt(1), pos.getSideAt(0) });
    }

    if(pos.size() == 3){
        lFaceletPosition.push_back({ pos.getSideAt(0), pos.getSideAt(1), pos.getSideAt(2) });
        lFaceletPosition.push_back({ pos.getSideAt(1), pos.getSideAt(2), pos.getSideAt(0) });
        lFaceletPosition.push_back({ pos.getSideAt(2), pos.getSideAt(0), pos.getSideAt(1) });
    }

    return lFaceletPosition;
};

vecFacelet Cubelet::getFacelet() const{
    return vFacelet;
}

Facelet Cubelet::getFacelet(const FaceletPosition& fp) const{
    CubeletPosition cp(fp);
    if(cp != pos)
        throw std::out_of_range(std::string() + __func__ + ": Requested Facelet is not in this Cubelet. Check your FaceletPosition.");

    Facelet f_ret;
    for(const auto& f_tmp : vFacelet){
        if(f_tmp.getPosition() == fp){
            f_ret = f_tmp;
            break;
        }
    }
    return f_ret;
}

std::ostream& operator<<(std::ostream& os, Cubelet C){
    os << "Facelet(s): {";

    for(const auto& flet: C.vFacelet)
        os << " (" << flet.side() << ", " << flet.getColor() << ") ";

    os << "}";
    return os;
}

bool operator==(const Cubelet& lhs, const Cubelet& rhs){
    if( lhs.pos != rhs.pos)
        return false;

    for(const auto& fp: lhs.getFaceletPositionList()){
        if(lhs.getFacelet(fp) != rhs.getFacelet(fp))
            return false;
    }

    return true;
}


Cubelet& Cubelet::operator*=(const FaceSide& rhs){
    if(rhs == undefside)
        throw std::runtime_error(__func__ + std::string(": Cubelet multiplication with undefside is not allowed."));

    for(auto& fl: vFacelet)
        fl *= rhs;

    pos *= rhs;
    return *this;
};



CubeletPosition::operator std::size_t() const{
    if(size() == 0)
        throw std::runtime_error(std::string() + __func__ + ": CubeletPosition must be instantiated with at least one FaceSide." );

    FaceSide fac0 = getSideAt(0);
    FaceSide fac1 = getSideAt(1);
    FaceSide fac2 = getSideAt(2);

    if(fac1 == undefside && fac2 == undefside)
        return fac0;    //This covers all the Center CubeletPositions, assignment from 0 till 5 is covered here

    if(fac0 > fac1)
        std::swap(fac0, fac1);
    if(fac1 > fac2)
        std::swap(fac1, fac2);
    if(fac0 > fac1)
        std::swap(fac0, fac1);

    if(fac1 != undefside && fac2 == undefside){

        if(fac0 == front && fac1 == up) return 6;
        if(fac0 == front && fac1 == down) return 7;
        if(fac0 == front && fac1 == left) return 8;
        if(fac0 == front && fac1 == right) return 9;

        if(fac0 == back && fac1 == up) return 10;
        if(fac0 == back && fac1 == down) return 11;
        if(fac0 == back && fac1 == left) return 12;
        if(fac0 == back && fac1 == right) return 13;

        if(fac0 == up && fac1 == left) return 14;
        if(fac0 == up && fac1 == right) return 15;

        if(fac0 == down && fac1 == left) return 16;
        if(fac0 == down && fac1 == right) return 17;

    }

    if(fac1 != undefside && fac2 != undefside){

        if(fac0 == front && fac1 == up && fac2 == left) return 18;
        if(fac0 == front && fac1 == up && fac2 == right) return 19;
        if(fac0 == front && fac1 == down && fac2 == left) return 20;
        if(fac0 == front && fac1 == down && fac2 == right) return 21;

        if(fac0 == back && fac1 == up && fac2 == left) return 22;
        if(fac0 == back && fac1 == up && fac2 == right) return 23;
        if(fac0 == back && fac1 == down && fac2 == left) return 24;
        if(fac0 == back && fac1 == down && fac2 == right) return 25;

    }

    //Execution should never reach this point
    return -1;
}
