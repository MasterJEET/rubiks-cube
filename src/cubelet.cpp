/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "cubelet.h"


arrFacelet Cubelet::aFacelet; 

std::ostream& operator<<(std::ostream& os, CubeletPosition CP){
    return os << Position(CP.vecSide);
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


Cubelet::Cubelet(Facelet fac1): pos( fac1.side() ) {
    FaceletPosition fp1 = fac1.getPosition();
    aFacelet[ fp1 ] = fac1;
}

Cubelet::Cubelet(Facelet fac1, Facelet fac2): pos( fac1.side(), fac2.side() ) {
    
    FaceletPosition fp1 = fac1.getPosition();
    FaceletPosition fp2 = fac2.getPosition();
    CubeletPosition cp1(fp1);
    CubeletPosition cp2(fp2);
    if(cp1 != cp2)
        throw std::runtime_error(std::string() + __func__ + ": Two Facelets provided doesnot belong to same Cubelet");
    aFacelet[ fp1 ] = fac1;
    aFacelet[ fp2 ] = fac2;
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
    aFacelet[ fp1 ] = fac1;
    aFacelet[ fp2 ] = fac2;
    aFacelet[ fp3 ] = fac3;
}

Cubelet::Cubelet(std::vector<Facelet> _vecFac) {
    switch( _vecFac.size() ){
        case 1:
            {
            FaceletPosition fp1 = _vecFac[0].getPosition();
            pos = CubeletPosition( fp1 );
            aFacelet[ fp1 ] = _vecFac[0];
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
            aFacelet[ fp1 ] = _vecFac[0];
            aFacelet[ fp2 ] = _vecFac[1];
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
            aFacelet[ fp1 ] = _vecFac[0];
            aFacelet[ fp2 ] = _vecFac[1];
            aFacelet[ fp3 ] = _vecFac[2];
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

listFacelet Cubelet::getFaceletList() const{
    listFacelet lFacelet;
    for(const auto& fp: getFaceletPositionList())
        lFacelet.push_back( aFacelet[fp] );
    return lFacelet;
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
        flet = C.aFacelet.at(fpos);
        os << " (" << flet.side() << ", " << flet.getColor() << ") ";
    }

    if(fside0 != undefside && fside1 != undefside){
        fpos = FaceletPosition(fside1, fside0);
        flet = C.aFacelet.at(fpos);
        os << " (" << flet.side() << ", " << flet.getColor() << ") ";
    }

    if(fside0 != undefside && fside1 != undefside && fside2 != undefside){
        fpos = FaceletPosition(fside2, fside1, fside0);
        flet = C.aFacelet.at(fpos);
        os << " (" << flet.side() << ", " << flet.getColor() << ") ";
    }

    os << "}";
    return os;
}

bool operator==(const Cubelet& lhs, const Cubelet& rhs){
    if( lhs.pos != rhs.pos)
        return false;

    if( lhs.pos.size() == 1 ){
        return ( lhs.getFacelet( lhs.getPosition().getSideAt(0) ) == rhs.getFacelet( lhs.getPosition().getSideAt(0) ) );
    }

    if( lhs.pos.size() == 2 ){
        Position p_tmp( lhs.getPosition() );
        Facelet lfl0_tmp( lhs.getFacelet({ p_tmp.getSideAt(0), p_tmp.getSideAt(1) }) );
        Facelet rfl0_tmp( rhs.getFacelet({ p_tmp.getSideAt(0), p_tmp.getSideAt(1) }) );
        Facelet lfl1_tmp( lhs.getFacelet({ p_tmp.getSideAt(1), p_tmp.getSideAt(0) }) );
        Facelet rfl1_tmp( rhs.getFacelet({ p_tmp.getSideAt(1), p_tmp.getSideAt(0) }) );
        return ( lfl0_tmp == rfl0_tmp && lfl1_tmp == rfl1_tmp );
    }

    if( lhs.pos.size() == 3 ){
        Position p_tmp( lhs.getPosition() );
        Facelet lfl0_tmp( lhs.getFacelet({ p_tmp.getSideAt(0), p_tmp.getSideAt(1), p_tmp.getSideAt(2) }) );
        Facelet rfl0_tmp( rhs.getFacelet({ p_tmp.getSideAt(0), p_tmp.getSideAt(1), p_tmp.getSideAt(2) }) );
        Facelet lfl1_tmp( lhs.getFacelet({ p_tmp.getSideAt(1), p_tmp.getSideAt(2), p_tmp.getSideAt(0) }) );
        Facelet rfl1_tmp( rhs.getFacelet({ p_tmp.getSideAt(1), p_tmp.getSideAt(2), p_tmp.getSideAt(0) }) );
        Facelet lfl2_tmp( lhs.getFacelet({ p_tmp.getSideAt(2), p_tmp.getSideAt(0), p_tmp.getSideAt(1) }) );
        Facelet rfl2_tmp( rhs.getFacelet({ p_tmp.getSideAt(2), p_tmp.getSideAt(0), p_tmp.getSideAt(1) }) );
        return ( lfl0_tmp == rfl0_tmp && lfl1_tmp == rfl1_tmp && lfl2_tmp == rfl2_tmp );
    }

    //This return covers the case when pos.size() = 0
    return true;
}


/*
 * Suppose we multiply Cubelet on Position p1(up,right,front) with FaceSide Up,
 * It will update Cubelet parameters as if it has been relocated to Position p2(up,front,left).
 * FaceSide components of Positions will be multiplied with given FaceSide. New CubeletPosition is attained as if
 * Cube was rotated about axis perpendicular to 'given FaceSide (rhs)' in a clockwise fashion as viewed from 'given FaceSide'.
 * Note that its index is not updated in array as simultaneous update of other Cubelets is required
 *
 * p1*Up = Position(up,right,front)*Up = Position(up*Up,right*Up,front*Up) = Position(up,front,left) = p2
 *
 * */
Cubelet& Cubelet::operator*=(const FaceSide& rhs){
    if(rhs == undefside)
        throw std::runtime_error(__func__ + std::string(": Cubelet multiplication with undefside is not allowed."));

    for(auto& fl: getFaceletList())
        fl *= rhs;

    pos *= rhs;
    return *this;
};

