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
        const std::vector<FaceSide *> vecSide;                                              //Holds FaceSides
        const PositionType ptype;                                                         //Holds PositionType
    public:
        Position(FaceSide *first);                                                   //For initailizing a FaceSide from parameter, specifies which center
        Position(FaceSide *first, FaceSide *second);                                  //For initializing two FaceSides from parameter list, specifies which edge
        Position(FaceSide *first, FaceSide *second, FaceSide *third);                  //For initializing all three FaceSides from parameter list, specifies which corner
        const std::vector<FaceSide *> *getSide();                                           //Returns pointer to 'vecSide'
        const PositionType *getType();                                                    //Returns pointer to 'ptype'
};

std::ostream& operator<<(std::ostream& os, Position P);

#endif
