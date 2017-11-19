/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "facelet.h"


Facelet& Facelet::operator*=(const FaceSide& rhs){
    pos *= rhs;
    return *this;
}


///Definition of friend function of class FaceletPosition

bool operator==(const FaceletPosition& lhs, const FaceletPosition& rhs){
    ///First FaceSides must be equal, point 2.a descrived above
    if( lhs.getSideAt(0) != rhs.getSideAt(0) )
        return false;

    ///2nd and 3rd FaceSide equal in same order, 2.b.i describe above
    if ( lhs.getSideAt(1) == rhs.getSideAt(1) && lhs.getSideAt(2) == rhs.getSideAt(2) )
        return true;

    ///2nd and 3rd FaceSide equal in rever order, 2.b.ii described above
    if ( lhs.getSideAt(1) == rhs.getSideAt(2) && lhs.getSideAt(2) == rhs.getSideAt(1) )
        return true;

    ///If above conditions doesn't satisfy return false
    return false;
    
}


FaceletPosition& FaceletPosition::operator*=(const FaceSide& rhs){
    for(auto& el:vecSide){
        el *= rhs;
    }    
    return *this;
}


///bool operator<(const FaceletPosition& lhs, const FaceletPosition& rhs){
///    size_t size1 = lhs.size();
///    size_t size2 = rhs.size();
///
///    ///when both are empty
///    if( size1 == 0 && size2 == 0)
///        return false;
///
///    ///when only lhs is empty, return true as an "empty is less than something"
///    if( size1 == 0 )
///        return true;
///
///    ///when only rhs is empty, return false as "something is greater than empty"
///    if( size2 == 0 )
///        return false;
///
///    ///when both have non-empty size
///    if( lhs.getSideAt(0) < rhs.getSideAt(0) )
///        return true;
///    if( lhs.getSideAt(0) > rhs.getSideAt(0) )
///        return false;
///
///    ///when first FaceSides in lhs and rhs are equal and lhs.size == 1 and rhs.size == 1
///    ///Then both are equal and return false
///    if( size1 == 1 && size2 == 1 )
///        return false;
///    ///when first FaceSides in lhs and rhs are equal and lhs.size > 1 and rhs.size = 1
///    ///then return false
///    if( size1 > 1 && size2 == 1)
///        return false;
///    ///when first FaceSides in lhs and rhs are equal and lhs.size == 1 and rhs.size > 1
///    ///then return true
///    if( size1 == 1 && size2 > 1)
///        return true;
///
///}
