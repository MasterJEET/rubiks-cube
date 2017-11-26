/*! \file   facelet.h
 *  \brief  Contains 'class Facelet', 'class FaceletPosition' & related global functions
 *
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#ifndef FACELET_H
#define FACELET_H

#include "position.h"
#include <ostream>

class FaceletPosition: public Position  {
    public:
        ///All constructor similar to those in base class Position
        FaceletPosition(){};
        FaceletPosition(const FaceSide first): Position(first){};
        FaceletPosition(const FaceSide first, const FaceSide second): Position(first, second){};
        FaceletPosition(const FaceSide first, const FaceSide second, const FaceSide third): Position(first, second, third){};
        FaceletPosition(const std::vector<FaceSide> _vecSide): Position(_vecSide){};

        ///operator<< overloading to write FaceletPosition to ostream
        friend std::ostream& operator<<(std::ostream& os, FaceletPosition FP);

        ///Equality
        friend bool operator==(const FaceletPosition& lhs, const FaceletPosition& rhs);

        ///Inequality
        friend bool operator!=(const FaceletPosition& lhs, const FaceletPosition& rhs){ return !(lhs == rhs); }

        ///Multiplication, modify object
        FaceletPosition& operator*=(const FaceSide& rhs);

        ///Multiplication, return object copy
        friend FaceletPosition operator*(FaceletPosition lhs, const FaceSide& rhs){ lhs *= rhs; return lhs; }

        /*! Type operator, converting to size_t to be used as array index later
         *
         * Conversion is aimed at assigning each Facelet of cube an unique number specific to its position,
         * i.e. assign each FaceletPosition a unique number
         *
         * For this purpose each FaceSide (which have nine Facelets) is thought of an unit and
         * assigned an unique number between 0 to 5 (as there are total of 6 FaceSides).
         * And each Facelet in a FaceSide is assigned a unique number between 0 to 8 (guess why?).
         * Using these two, unique numbers can be assigned to each FaceletPosition as computed in the code.
         *
         */
        operator std::size_t() const;

};


typedef std::vector<FaceletPosition> vecFletPos;


class Facelet {
    private:

        ///Holds face color
        Color col;
        FaceletPosition pos;
    public:
        ///Default constructor
        Facelet(){};

        ///Initialization from Color and FaceSice
        Facelet(const Color _col, const FaceletPosition _pos):col(_col), pos(_pos) {}
        
        ///Initialization from FaceSice and Color
        Facelet(const FaceletPosition _pos, const Color _col): Facelet(_col, _pos) {}

        ///Returns pointer to 'col'
        Color getColor() const { return col; }
        
        ///Returns of Facelet
        FaceletPosition getPosition() const { return pos; }

        ///Returns which FaceSide given Facelet is located at
        FaceSide side() const { return pos.getSideAt(0); }

        ///Sets 'side'
        void setPosition(const FaceletPosition _pos) { pos = _pos; }

        ///Overloading operator*= to define multiplication of type
        ///Facelet*=FaceSide
        Facelet& operator*=(const FaceSide& rhs); 

        ///Overloading operator* to define multiplication of type
        ///Facelet*FaceSide
        friend Facelet operator*(Facelet lhs, const FaceSide& rhs){ lhs *= rhs; return lhs; }

        ///Equality 
        friend bool operator==(const Facelet& lhs, const Facelet& rhs) { return  lhs.col == rhs.col && lhs.side() == rhs.side(); }

        ///Inequality
        friend bool operator!=(const Facelet& lhs, const Facelet& rhs) { return !( lhs == rhs ); }

        ///Write to output stream
        friend std::ostream& operator<<(std::ostream& os, const Facelet& F){ return os << "Facelet: col = " << F.col << ", side = " << F.side(); }

        ///Check if given two faclets are opposite of each other
        friend bool areOpposite(const Facelet& first, const Facelet& second){ return areOpposite(first.side(), second.side()); }

        ///Check if any of given three Facelets contain opposite faces
        friend bool anyOpposite(const Facelet& first, const Facelet& second, const Facelet& third){ return anyOpposite(first.side(), second.side(), third.side()); }
};


/*! \fn vecFletPos vecEdgeEquFletPos(const FaceSide& f)
 *  \brief  This function retuns (vector of) up, right, down & left (in this order)
 *  edge (Facelet)Position equivalence of FaceSide 'f'.
 *
 * This exactly same as vecEdgeEquCletPos (defined in cubelet.h) except we return
 * vector of FaceletPositon instead of CubeletPosition. FaceletPosition fp_u be 'up' edge
 * equivalent of FaceSide f = left. Then we write
 *
 *      fe(up,f) = fp_u
 *
 * Note: For any FaceSie f and x, we have
 *      * fe(x,f) = FaceletPosition(f,x(f)) //here f must be first parameter
 *      * fe(x,front) = FaceletPosition(f,x)    //see common.h for definition of x(f)
 *
 * */
vecFletPos vecEdgeEquFletPos(const FaceSide& f);

#endif
