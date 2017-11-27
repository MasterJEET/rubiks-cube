/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "facelet.h"

std::ostream& operator<<(std::ostream& os, FaceletPosition FP){
    return os << Position(FP.vecSide);
}



bool operator==(const FaceletPosition& lhs, const FaceletPosition& rhs){
    //First FaceSides must be equal
    if( lhs.getSideAt(0) != rhs.getSideAt(0) )
        return false;

    //2nd and 3rd FaceSide equal in same order
    if ( lhs.getSideAt(1) == rhs.getSideAt(1) && lhs.getSideAt(2) == rhs.getSideAt(2) )
        return true;

    //2nd and 3rd FaceSide equal in rever order
    if ( lhs.getSideAt(1) == rhs.getSideAt(2) && lhs.getSideAt(2) == rhs.getSideAt(1) )
        return true;

    return false;
    
}


FaceletPosition& FaceletPosition::operator*=(const FaceSide& rhs){
    if(rhs == undefside)
        throw std::runtime_error(__func__ + std::string(": FaceletPosition multiplication with undefside not allowed"));
    for(auto& el:vecSide){
        el *= rhs;
    }    
    return *this;
}

FaceletPosition::operator std::size_t() const{

    if(size() == 0)
        throw std::runtime_error(std::string() + __func__ + ": FaceletPosition must be instantiated with at least one FaceSide." );


    // FaceSide being an enum, each of its values are basically integer type (with unique value) and thus unique number for each FaceSide is automatically defined
    std::size_t num_faceside = getSideAt(0);


    // Evaluating unique number for each FaceletPosition within a given FaceSide by rotating it to front and assigning a number (0-8) to front FaceletPositions

    std::size_t num_facelet;

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

    // Finally assigning an integer between 0 to _MAX_-1 to FaceletPosition
    return num_faceside*9 + num_facelet;
}


Facelet& Facelet::operator*=(const FaceSide& rhs){
    pos *= rhs;
    return *this;
}

