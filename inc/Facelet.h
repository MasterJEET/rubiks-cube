/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#ifndef FACELET_H
#define FACELET_H

#include "common.h"
#include <ostream>

class Facelet {
    private:

        //Holds face color
        const Color * const col;
        const FaceSide *side;
    public:
        
        //Initialization from Color and FaceSice
        Facelet(const Color * const col, const FaceSide *side);
        
        //Returns pointer to 'col'
        const Color * const getColor();
        
        //Returns 'side'
        const FaceSide * const getFaceSide();
        
        //Sets 'side'
        void setFaceSide(const FaceSide * const side);
};

std::ostream& operator<<(std::ostream& os, Facelet F);

#endif
