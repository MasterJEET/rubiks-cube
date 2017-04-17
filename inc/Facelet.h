/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#ifndef FACELET_H
#define FACELET_H

#include "Position.h"
#include "common.h"

//enum Color { White, Yellow, Orange, Red, Green, Blue, C_UNDEFINED = -1 };

class Facelet {
    private:
        Color col;
        Position pos;
    public:
        Facelet();                                                                  //Default constructor
        Facelet(Color col);                                                         //Initialization from Color
        Facelet(Position pos);                                                      //Initialization from Position
        Facelet(Color col, Position pos);                                           //Initialization from Color and Position
        Color *getColor();                                                          //Returns pointer to 'col'
        Position *getPosition();                                                    //Returns pointer to 'pos'
        PositionType *getPositionType();                                            //Returns pointer to 'ptype of pos'
        FaceSide *getFaceSide();
        void setColor(Color col);
        void setPosition(Position pos);
};

#endif
