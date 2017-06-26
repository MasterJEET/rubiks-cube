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
