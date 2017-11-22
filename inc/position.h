/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#ifndef POSITION_H
#define POSITION_H

#include <vector>
#include <stdexcept>
#include <functional>
#include "common.h"


class Position {
    protected:
        
        ///Holds FaceSides
        std::vector<FaceSide> vecSide;
        
        ///Holds PositionType
        PositionType ptype;

    public:
        ///Default constructor
        Position(){};

        ///For initializing any number (1-3) of FaceSides, this constructor is intended to
        //delegated from other constructors
        Position(const FaceSide first,const FaceSide second = undefside,const FaceSide third = undefside): Position( std::vector<FaceSide>({first,second,third}) ){};
        
        ///Initialization from vector for FaceSides
        Position(const std::vector<FaceSide> _vecSide);

        ///Returns pointer to 'vecSide'
        const std::vector<FaceSide> * getSide() const{ return &(this->vecSide); }

        ///Returns FaceSide present at 'vecSide[index]'
        FaceSide getSideAt(size_t index) const;
        
        ///Returns pointer to 'ptype'
        PositionType getPositionType() const {return ptype; }

        ///Number of FaceSides with valid (not undefside) value
        size_t size() const{ return vecSide.size()==0 ? 0 : (vecSide[0] != undefside) + (vecSide[1] != undefside) + (vecSide[2] != undefside);}

        ///operator<< overloading to write Position to ostream
        friend std::ostream& operator<<(std::ostream& os, Position P);

        ///Equality
        friend bool operator==(const Position& lhs, const Position& rhs);

        ///Inequality
        friend bool operator!=(const Position& lhs, const Position& rhs){ return !(lhs == rhs); }

        ///Multiplication, modify object
        Position& operator*=(const FaceSide& rhs);

        ///Multiplication, return object copy
        friend Position operator*(Position lhs, const FaceSide& rhs){ lhs *= rhs; return lhs; }

        ///Type operator, converting to size_t to be used as array index later
        operator std::size_t() const;
};


#endif
