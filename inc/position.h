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
        FaceSide getSideAt(size_t index) const;
        
        //Returns pointer to 'ptype'
        PositionType getPositionType() const;

};

std::ostream& operator<<(std::ostream& os, Position P);





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
        struct hash<Position> {
            typedef Position argument_type;
            typedef std::size_t result_type;
            
            result_type operator()(const argument_type& p) const{
                FaceSide f1 = p.getSideAt(0);
                FaceSide f2 = p.getSideAt(1);
                FaceSide f3 = p.getSideAt(2);

                // Swap values of f2 and f3 if f2 < f3
                // This is required to make this implementaion
                // insensitive to order of 2nd and 3rd FaceSide
                if(f2 < f3){
                    FaceSide ftmp = f2;
                    f2 = f3;
                    f3 = ftmp;
                }

                result_type i1 = std::hash<int>()(static_cast<result_type>(f1));
                result_type i2 = std::hash<int>()(static_cast<result_type>(f2));
                result_type i3 = std::hash<int>()(static_cast<result_type>(f3));

                return ( i1*100 + i2*10 + i3 );
            }
        };
}

#endif
