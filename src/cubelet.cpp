/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "cubelet.h"


hashFacelet Cubelet::hFacelet;

Cubelet::Cubelet(Facelet fac1): pos( fac1.side() ) {
    FaceletPosition fp1 = fac1.getPosition();
    hFacelet[ fp1 ] = fac1;
}

Cubelet::Cubelet(Facelet fac1, Facelet fac2): pos( fac1.side(), fac2.side() ) {
    
    FaceletPosition fp1 = fac1.getPosition();
    FaceletPosition fp2 = fac2.getPosition();
    CubeletPosition cp1(fp1);
    CubeletPosition cp2(fp2);
    if(cp1 != cp2)
        throw std::runtime_error(std::string() + __func__ + ": Two Facelets provided doesnot belong to same Cubelet");
    hFacelet[ fp1 ] = fac1;
    hFacelet[ fp2 ] = fac2;
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
    hFacelet[ fp1 ] = fac1;
    hFacelet[ fp2 ] = fac2;
    hFacelet[ fp3 ] = fac3;
}

Cubelet::Cubelet(std::vector<Facelet> _vecFac) {
    switch( _vecFac.size() ){
        case 1:
            {
            FaceletPosition fp1 = _vecFac[0].getPosition();
            pos = CubeletPosition( fp1 );
            hFacelet[ fp1 ] = _vecFac[0];
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
            hFacelet[ fp1 ] = _vecFac[0];
            hFacelet[ fp2 ] = _vecFac[1];
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
            hFacelet[ fp1 ] = _vecFac[0];
            hFacelet[ fp2 ] = _vecFac[1];
            hFacelet[ fp3 ] = _vecFac[2];
            break;
            }
        default:
            throw std::runtime_error(std::string() + __func__ + ": _vecFac can only have size such that 0 < size <= 3...");
            
    }
}

std::ostream& operator<<(std::ostream& os, Cubelet C){
    os << "Facelet(s): {";
    FaceSide fside0 = C.pos.getSideAt(0);
    FaceSide fside1 = C.pos.getSideAt(1);
    FaceSide fside2 = C.pos.getSideAt(2);

    Facelet flet;
    FaceletPosition fpos;
    if(fside0 != undefside){
        fpos = FaceletPosition(fside0);
        flet = C.hFacelet.at(fpos);
        os << " (" << flet.side() << ", " << flet.getColor() << ") ";
    }

    if(fside0 != undefside && fside1 != undefside){
        fpos = FaceletPosition(fside1, fside0);
        flet = C.hFacelet.at(fpos);
        os << " (" << flet.side() << ", " << flet.getColor() << ") ";
    }

    if(fside0 != undefside && fside1 != undefside && fside2 != undefside){
        fpos = FaceletPosition(fside2, fside1, fside0);
        flet = C.hFacelet.at(fpos);
        os << " (" << flet.side() << ", " << flet.getColor() << ") ";
    }

    os << "}";
    return os;
}

bool operator==(const Cubelet& lhs, const Cubelet& rhs){
    if( lhs.pos != rhs.pos)
        return false;

    if(lhs.hFacelet != rhs.hFacelet)
        return false;

    return true;
}


///Equality
bool operator==(const CubeletPosition& lhs, const CubeletPosition& rhs){
   ///sorting FaceSides of lhs
   FaceSide lfs0 = lhs.getSideAt(0);
   FaceSide lfs1 = lhs.getSideAt(1);
   FaceSide lfs2 = lhs.getSideAt(2);

   if( lfs0 > lfs1 )
       std::swap(lfs0, lfs1);
   if( lfs1 > lfs2 )
       std::swap(lfs1, lfs2);
   if( lfs0 > lfs1 )
       std::swap(lfs0, lfs1);
   ///sorting FaceSides of rhs
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


/*
 * Suppose we multiply Cubelet on Position p1(up,right,front) with FaceSide Up,
 * It will relocate to Position p2(up,front,left). FaceSide components of Positions will be multiplied with given FaceSide. New Cubelet Position is attained as if
 * Cube was rotated about axis perpendicular to 'given FaceSide (rhs)' in a clockwise fashion as viewed from 'given FaceSide'
 *
 * p1*Up = Position(up,right,front)*Up = Position(up*Up,right*Up,front*Up) = Position(up,front,left) = p2
 *
 * */
Cubelet& Cubelet::operator*=(const FaceSide& rhs){
    hashFacelet::iterator it = hFacelet.begin();
    while( it != hFacelet.end()){
        //if key need to be changed
        if( it->first * rhs != it->first  ){
            //Inserting new entry with updated key-value
            hFacelet[ it->first * rhs ] = it->second * rhs;
            //Deleting obsolete entry
            it = hFacelet.erase(it);
        }
        else
        //if key need not be changed
        {
            it->second *= rhs;
            it++;
        }
    }
    pos *= rhs;
    return *this;
};
