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

typedef CollectionWrapper<FaceSide,false> Position;
typedef CollectionWrapper<FaceSide,true> FaceletPosition;
typedef std::vector<FaceletPosition> vecFletPos;

FaceletPosition relative(const FaceletPosition&, const FaceletPosition&);


class Facelet {
    private:

        ///Holds face color
        Color col;
        FaceletPosition pos;
    public:
        ///Default constructor
        Facelet():col(undefcol){};

        ///Initialization from Color and FaceSice
        Facelet(const Color _col, const FaceletPosition _pos):col(_col), pos(_pos) {}
        
        ///Initialization from FaceSice and Color
        Facelet(const FaceletPosition _pos, const Color _col): Facelet(_col, _pos) {}

        ///Returns pointer to 'col'
        Color getColor() const { return col; }
        
        ///Returns of Facelet
        FaceletPosition getPosition() const { return pos; }

        ///Returns which FaceSide given Facelet is located at
        FaceSide side() const { return pos.first(); }

        ////Sets 'side'
        //void setPosition(const FaceletPosition _pos) { pos = _pos; }

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

        ///Colored output format for Color
        std::string colorFormat();

        ///Check if given two faclets are opposite of each other
        friend bool areOpposite(const Facelet& first, const Facelet& second){ return areOpposite(first.side(), second.side()); }

        ///Check if any of given three Facelets contain opposite faces
        friend bool anyOpposite(const Facelet& first, const Facelet& second, const Facelet& third){ return anyOpposite(first.side(), second.side(), third.side()); }
};


#endif
