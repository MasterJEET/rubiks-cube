/*! \file   cubelet.h
 *  \brief  Contains 'class Cubelet', 'class CubeletPosition' & related global function declarations
 * 
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 17th Apr 2017
 *
 * */

#ifndef CUBELET_H
#define CUBELET_H


#include "facelet.h"
#include "position.h"
#include <vector>
#include <array>
#include <list>

typedef std::vector<Facelet> vecFacelet;
typedef std::list<FaceletPosition> listFaceletPosition;


class CubeletPosition : public Position {
    public:
        ///Constructors same as those of Position
        CubeletPosition(){};
        CubeletPosition(const FaceSide first): Position(first){};
        CubeletPosition(const FaceSide first, const FaceSide second): Position(first, second){};
        CubeletPosition(const FaceSide first, const FaceSide second, const FaceSide third): Position(first, second, third){};
        CubeletPosition(const std::vector<FaceSide> _vecSide): Position(_vecSide){};
        
        ///initialize from  FaceletPosition
        CubeletPosition(const FaceletPosition& fp): Position( fp.getSide() ){};

        ///operator<< overloading to write CubeletPosition to ostream
        friend std::ostream& operator<<(std::ostream& os, CubeletPosition P);

        ///Equality
        friend bool operator==(const CubeletPosition& lhs, const CubeletPosition& rhs);

        ///Inequality
        friend bool operator!=(const CubeletPosition& lhs, const CubeletPosition& rhs){ return !(lhs == rhs); }

        /** Type operator, converting to size_t to be used as array index later
         *
         * Here we simply list and assign unique numbers (between 0 to 25) to each Cubelets.
         * Although there is a return statement with a negative integer, execution should never reach that point.
         *
         * */
        operator std::size_t() const;
};

typedef std::vector<CubeletPosition> vecCletPos;

class Cubelet{

    private:

        ///to hold Facelets in vector with FaceletPosition as index
        vecFacelet vFacelet;
        ///Holds Position of Cubelet in the Cube
        CubeletPosition pos;

    public:

        Cubelet(){};
        
        ///Constructor for Center cubelets
        Cubelet(Facelet fac1): Cubelet(vecFacelet{fac1}){};
        
        ///Constructor for Edge cubelets
        Cubelet(Facelet fac1, Facelet fac2): Cubelet(vecFacelet{fac1,fac2}) {};
        
        ///Constructor for Corner cubelets
        Cubelet(Facelet fac1, Facelet fac2, Facelet fac3): Cubelet(vecFacelet{fac1,fac2,fac3}) {};

        ///Initializaton from vector of Facelets
        Cubelet( vecFacelet _vecFac );
       
        ///Return list of FaceletPostions associated with this Cubelet
        listFaceletPosition getFaceletPositionList() const;

        ///Fetch all of Facelets in this Cubelet
        vecFacelet getFacelet() const;

        ///Returns Facelet at given FaceletPositon 
        Facelet getFacelet(const FaceletPosition& fp) const;

        ///Returns Position
        CubeletPosition getPosition() const{ return pos;}

        ///Sets Position for cubelet
        void setPosition(const CubeletPosition _pos){ pos = _pos; }

        ///operator<< overloading for writing Cubelet to ostream
        friend std::ostream& operator<<(std::ostream& os, Cubelet C);

        ///Equality
        friend bool operator==(const Cubelet& lhs, const Cubelet& rhs);

        ///Inequality
        friend bool operator!=(const Cubelet& lhs, const Cubelet& rhs){ return !(lhs == rhs); }

        /** Rotate about axis defined by FaceSide, change the object
         *
         * Suppose we multiply Cubelet on Position p1(up,right,front) with FaceSide Up,
         * It will update Cubelet parameters as if it has been relocated to Position p2(up,front,left).
         * FaceSide components of Positions will be multiplied with given FaceSide. New CubeletPosition is attained as if
         * Cube was rotated about axis perpendicular to 'given FaceSide (rhs)' in a clockwise fashion as viewed from 'given FaceSide'.
         * Note that its index is not updated in array as simultaneous update of other Cubelets is required
         *
         * p1*Up = Position(up,right,front)*Up = Position(up*Up,right*Up,front*Up) = Position(up,front,left) = p2
         *
         * */
        Cubelet& operator*=(const FaceSide& rhs);

        /// Rotate about axis defined by FaceSide, return the object
        friend Cubelet operator*(Cubelet lhs, const FaceSide& rhs){ lhs *= rhs; return lhs; }
        
        friend class Cube;

};

#endif
