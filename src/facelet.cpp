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

Facelet& Facelet::operator*=(const FaceSide& rhs){
    side *= rhs;
    return *this;
}


//Definition of freind function of class FaceletPosition

bool operator==(const FaceletPosition& lhs, const FaceletPosition& rhs){
    //First FaceSides must be equal, point 2.a descrived above
    if( lhs.getSideAt(0) != rhs.getSideAt(0) )
        return false;

    //2nd and 3rd FaceSide equal in same order, 2.b.i describe above
    if ( lhs.getSideAt(1) == rhs.getSideAt(1) && lhs.getSideAt(2) == rhs.getSideAt(2) )
        return true;

    //2nd and 3rd FaceSide equal in rever order, 2.b.ii described above
    if ( lhs.getSideAt(1) == rhs.getSideAt(2) && lhs.getSideAt(2) == rhs.getSideAt(1) )
        return true;

    //If above conditions doesn't satisfy return false
    return false;
    
}
