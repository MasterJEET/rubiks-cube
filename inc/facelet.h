/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#ifndef FACELET_H
#define FACELET_H

#include "position.h"
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



class FaceletPosition: public Position  {
    public:
        //All constructor similar to those in base class Position
        FaceletPosition(const FaceSide first): Position(first){};
        FaceletPosition(const FaceSide first, const FaceSide second): Position(first, second){};
        FaceletPosition(const FaceSide first, const FaceSide second, const FaceSide third): Position(first, second, third){};
        FaceletPosition(const std::vector<FaceSide> _vecSide): Position(_vecSide){};

        //Equality
        friend bool operator==(const FaceletPosition& lhs, const FaceletPosition& rhs);

        //Inequality
        friend bool operator!=(const FaceletPosition& lhs, const FaceletPosition& rhs){ return !(lhs == rhs); }

};

/* =============== Hash for Position ================
 * This is required so that it can be used as key in
 * std::unordered_map created in class Cube.
 * This hash funciton uses three objects of FaceSide
 * If Position objects has less than three
 * FaceSides, F_UNDEFINED is assumed by default.
 *
 * The std::unordered_map will store Position object as
 * key and Facelet object as value 
 *
 * - First FaceSide specifies on which Face the Facelet
 *   is present
 * - Last two FaceSides specify where in given Face the
 *   Facelet is present, Order for last two FaceSide is
 *   not important.
 *
 * Examples:
 *
 * Position P1(right);
 * // Should refer to center Facelet object of Right Face
 *
 * Position P2(right, up);
 * // Should refer to edge Facelet object of right Face near
 * // to Up Face
 *
 * Position P3(right, up, front);
 * // Refers to corner Facelet object of Right Face at 
 * // corner of right, up, front Faces
 *
 * Position P4(right, front, up);
 * // Should refers to same Facelet object as P3 as
 * // order does not matter for last FaceSides
 * ==================================================
 */

namespace std {
    template <>
        struct hash<FaceletPosition> {
            typedef FaceletPosition argument_type;
            typedef std::size_t result_type;
            
            result_type operator()(const argument_type& p) const{
                FaceSide f1 = p.getSideAt(0);
                FaceSide f2 = p.getSideAt(1);
                FaceSide f3 = p.getSideAt(2);

                // Swap values of f2 and f3 if f2 < f3
                // This is required to make this implementaion
                // insensitive to order of 2nd and 3rd FaceSide
                if(f2 < f3){
                    swap(f2, f3);
                }

                result_type i1 = std::hash<int>()(static_cast<result_type>(f1));
                result_type i2 = std::hash<int>()(static_cast<result_type>(f2));
                result_type i3 = std::hash<int>()(static_cast<result_type>(f3));

                return ( i1*100 + i2*10 + i3 );
            }
        };
}

#endif
