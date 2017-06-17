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
        const Color col;
        FaceSide side;
    public:
        
        //Initialization from Color and FaceSice
        Facelet(const Color , const FaceSide side);
        
        //Initialization from Color and FaceSice
        Facelet(const FaceSide side, const Color);

        //Returns pointer to 'col'
        Color getColor() const;
        
        //Returns 'side'
        FaceSide getFaceSide() const;
        
        //Sets 'side'
        void setFaceSide(const FaceSide side);
};

std::ostream& operator<<(std::ostream& os, Facelet F);

#endif
