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
#include "common.h"

class Position {
    private:
        
        //Holds FaceSides
        std::vector<FaceSide> vecSide;
        
        //Holds PositionType
        PositionType ptype;

    public:
        //Default constructor
        Position();

        //For initailizing a FaceSide from parameter, specifies which center
        Position(const FaceSide first);
        
        //For initializing two FaceSides from parameter list, specifies which edge
        Position(const FaceSide first,const FaceSide second);
        
        //For initializing all three FaceSides from parameter list, specifies which corner
        Position(const FaceSide first,const FaceSide second,const FaceSide third);
        
        //Returns pointer to 'vecSide'
        const std::vector<FaceSide> * getSide() const;

        //Returns FaceSide present at 'vecSide[index]'
        const FaceSide getSideAt(size_t index) const;
        
        //Returns pointer to 'ptype'
        const PositionType getPositionType() const;

};

std::ostream& operator<<(std::ostream& os, Position P);

#endif
