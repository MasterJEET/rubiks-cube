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

/**
 * Conversion is aimed at assigning each Facelet of cube an unique number specific to its position,
 * i.e. assign each position a unique number
 *
 * For this purpose each FaceSide (which have nine Facelets) is thought of an unit and assigned an unique number between 0 to 5 (as there are total of 6 FaceSides).
 * And each Facelet in a FaceSide is assigned a unique number between 0 to 8 (guess why?). Using these two, unique numbers can be assigned to each FaceletPosition as
 * computed in the code.
 *
 */
FaceletPosition::operator std::size_t() const{

    if(getSideAt(0) == undefside)
        throw std::runtime_error(std::string() + __func__ + ": FaceletPosition must be instantiated with at least one FaceSide." );

    /// FaceSide being an enum, each of its values are basically integer type (with unique value) and thus unique number for each FaceSide is automatically defined
    std::size_t num_faceside = getSideAt(0);

    // Evaluating unique number for each FaceletPosition within a given FaceSide by rotating it to front and assigning a number (0-8) to front FaceletPositions
    FaceSide fac0 = getSideAt(0);
    FaceSide fac1 = getSideAt(1);
    FaceSide fac2 = getSideAt(2);
    
    switch(fac0){
        case up:
            fac0 *= left;fac1 *= left;fac2 *= left;
            break;
        case right:
            fac0 *= up;fac1 *= up;fac2 *= up;
            break;
        case down:
            fac0 *= right;fac1 *= right;fac2 *= right;
            break;
        case left:
            fac0 *= down;fac1 *= down;fac2 *= down;
            break;
        case back: //Twice rotation is required to reach front
            fac0 *= up;fac1 *= up;fac2 *= up;
            fac0 *= up;fac1 *= up;fac2 *= up;
            break;
        default: //No rotation is required if it's already at front
            break;
    }

    std::size_t num_facelet;

    if(fac1 == undefside && fac2 == undefside)
        num_facelet = 0;

    if(fac1 != undefside && fac2 == undefside){
        switch(fac1){
            case up:
                num_facelet = 1;
                break;
            case right:
                num_facelet = 2;
                break;
            case down:
                num_facelet = 3;
                break;
            case left:
                num_facelet = 4;
                break;
            default:
                break;
        }
    }

    if(fac1 != undefside && fac2 != undefside){
        if( (fac1==up && fac2==right) || (fac2==up && fac1==right) )
            num_facelet = 5;
        if( (fac1==right && fac2==down) || (fac2==right && fac1==down) )
            num_facelet = 6;
        if( (fac1==down && fac2==left) || (fac2==down && fac1==left) )
            num_facelet = 7;
        if( (fac1==left && fac2==up) || (fac2==left && fac1==up) )
            num_facelet = 8;
    }

    return num_faceside*9 + num_facelet;
}
