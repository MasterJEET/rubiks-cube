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
        Color col;
        FaceSide side;
    public:
        //Default constructor
        Facelet(){};

        //Initialization from Color and FaceSice
        Facelet(const Color , const FaceSide side);
        
        //Initialization from FaceSice and Color
        Facelet(const FaceSide side, const Color);

        //Returns pointer to 'col'
        Color getColor() const { return col; }
        
        //Returns 'side'
        FaceSide getFaceSide() const { return side; }

        //Sets 'side'
        void setFaceSide(const FaceSide _side) { side = _side; }

        //Overloading operator*= to define multiplication of type
        //Facelet*=FaceSide
        Facelet& operator*=(const FaceSide& rhs); 

        //Overloading operator* to define multiplication of type
        //Facelet*FaceSide
        friend Facelet operator*(Facelet lhs, const FaceSide& rhs){ lhs *= rhs; return lhs; }

        //Equality 
        friend bool operator==(const Facelet& lhs, const Facelet& rhs) { return  lhs.col == rhs.col && lhs.side == rhs.side; }

        //Write to output stream
        friend std::ostream& operator<<(std::ostream& os, const Facelet& F){ return os << "Facelet: col = " << F.col << ", side = " << F.side; }

};


#endif
