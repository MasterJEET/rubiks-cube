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

class Facelet {
    private:
        const Color col;
        FaceSide *fac;
    public:
        Facelet(Color col);                                                         //Initialization from Color
        Facelet(Color col, FaceSide *fac);                                          //Initialization from Color and Position
        const Color *getColor();                                                    //Returns pointer to 'col'
        FaceSide *getFaceSide();                                                    //Returns 'fac'
        void setFaceSide(FaceSide *fac);                                            //Sets 'fac'
};

#endif
