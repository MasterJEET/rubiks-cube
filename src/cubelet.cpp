/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "cubelet.h"

Cubelet::Cubelet(Facelet fac1): pos( fac1.side() ) {
    FaceletPosition fp1 = fac1.getPosition();
    mFacelet[ fp1 ] = fac1;
}

Cubelet::Cubelet(Facelet fac1, Facelet fac2): pos( fac1.side(), fac2.side() ) {
    
    FaceletPosition fp1 = fac1.getPosition();
    FaceletPosition fp2 = fac2.getPosition();
    CubeletPosition cp1(fp1);
    CubeletPosition cp2(fp2);
    if(cp1 != cp2)
        throw std::runtime_error(std::string() + __func__ + ": Two Facelets provided doesnot belong to same Cubelet");
    mFacelet[ fp1 ] = fac1;
    mFacelet[ fp2 ] = fac2;
}

Cubelet::Cubelet(Facelet fac1, Facelet fac2, Facelet fac3): pos( fac1.side(), fac2.side(), fac3.side() ) {
    
    FaceletPosition fp1 = fac1.getPosition();
    FaceletPosition fp2 = fac2.getPosition();
    FaceletPosition fp3 = fac3.getPosition();
    CubeletPosition cp1(fp1);
    CubeletPosition cp2(fp2);
    CubeletPosition cp3(fp3);
    if(cp1 != cp2 || cp1 != cp3 || cp2 != cp3)
        throw std::runtime_error(std::string() + __func__ + ": Three Facelets provided doesnot belong to same Cubelet");
    mFacelet[ fp1 ] = fac1;
    mFacelet[ fp2 ] = fac2;
    mFacelet[ fp3 ] = fac3;
}

Cubelet::Cubelet(std::vector<Facelet> _vecFac) {
    switch( _vecFac.size() ){
        case 1:
            {
            FaceletPosition fp1 = _vecFac[0].getPosition();
            pos = CubeletPosition( fp1 );
            mFacelet[ fp1 ] = _vecFac[0];
            break;
            }
        case 2:
            {
            FaceletPosition fp1 = _vecFac[0].getPosition();
            FaceletPosition fp2 = _vecFac[1].getPosition();
            CubeletPosition cp1(fp1);
            CubeletPosition cp2(fp2);
            if(cp1 != cp2)
                throw std::runtime_error(std::string() + __func__ + ": Two Facelets provided doesnot belong to same Cubelet");
            pos = cp1 ;
            mFacelet[ fp1 ] = _vecFac[0];
            mFacelet[ fp2 ] = _vecFac[1];
            break;
            }
        case 3:
            {
            FaceletPosition fp1 = _vecFac[0].getPosition();
            FaceletPosition fp2 = _vecFac[1].getPosition();
            FaceletPosition fp3 = _vecFac[2].getPosition();
            CubeletPosition cp1(fp1);
            CubeletPosition cp2(fp2);
            CubeletPosition cp3(fp3);
            if(cp1 != cp2 || cp1 != cp3 || cp2 != cp3)
                throw std::runtime_error(std::string() + __func__ + ": Three Facelets provided doesnot belong to same Cubelet");
            mFacelet[ fp1 ] = _vecFac[0];
            mFacelet[ fp2 ] = _vecFac[0];
            mFacelet[ fp3 ] = _vecFac[0];
            break;
            }
        default:
            throw std::runtime_error(std::string() + __func__ + ": _vecFac can only have size such that 0 < size <= 3...");
            
    }
}

std::ostream& operator<<(std::ostream& os, Cubelet C){
    os << "Colors: { ";
    for(const auto& it: C.mFacelet)
        os << it.second.getColor() << " ";
    os << "} ";
    os << C.pos;
    return os;
}

bool operator==(const Cubelet& lhs, const Cubelet& rhs){
    if( lhs.pos != rhs.pos)
        return false;

    if(lhs.mFacelet.size() != rhs.mFacelet.size())
        return false;

    for( const auto& it: lhs.mFacelet )
        if( it.second != rhs.mFacelet.at( it.first ) )
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
