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
        
        ///New construtor, initialize from  FaceletPosition
        CubeletPosition(const FaceletPosition fp): Position( *fp.getSide() ){};

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


/*! \fn vecCletPos vecEdgeEquPosition(const FaceSide& f)
 *  \brief  This function retuns (vector of) up, right, down & left (in this order)
 *  edge Position equivalence of FaceSide 'f'.
 *
 * What are edge equivalent Positions?
 *
 * Observe the current orientation of Cube. If a FaceSide 'fs' is in horizontal plane (up or down),
 * rotate the cube about a horizontal axis parallel to front FaceSide till 'fs' coincide with the front.
 * Cubelet that's at edge (Cubelet)Position (front,up) now was let's say at Position 'p_fu_before'. Then 'p_fu_before'
 * is 'up edge equivalence of fs'. Let's denote it as
 *
 *      e(up,fs) = p_fu_before
 *
 * Note: For any FaceSide f and x
 *      * e(x,f) = CubeletPosition( x(f), f ) //where x(f) is x FaceSide equivalence of f, defined in common.h
 *      * e(x,front) = CubeletPosition( x(front), front) = Position(x,front) //Since x(front) = x
 *
 * Example: consider listing all edge equivalence of FaceSide f = down
 *      * e(up,f)       =   CubeletPosition(front,f)
 *      * e(right,f)    =   CubeletPosition(right,f)
 *      * e(down,f)     =   CubeletPosition(back,f)
 *      * e(left,f)     =   CubeletPosition(left,f)
 *
 * */
vecCletPos vecEdgeEquPosition(const FaceSide& f);


/*! \fn vecCletPos vecCornerEquPosition(const FaceSide& f)
 *  \brief  This function returns (a vector of) corner Position equivalence of FaceSide 'f'.
 *  Order of equivalence returned: {up,left}, {up,right}, {down,right}, {down,left}
 *
 * What are corner equivalent Positions?
 *
 * Similar to edge equivalent (Cubelet)Positions but here we consider corner Cubelets and their Positions, instead of Edges.
 * Let Position p_ul be "{up,left} corner equivalent position" of FaceSide f. Let's write it as
 *
 *      c(up,left,f) = p_ul
 *
 * Note: For any FaceSide f, x and y we have
 *      * c(x,y,f)  =   CubeletPosition(x(f), y(f), f) //For x(f) & y(f), see setEquivalentFaceSide defined in common.h
 *      * c(x,y,front)  = CubeletPosition(x,y,front)
 *
 * Example: list all corner equivalent Positions of FaceSide f = back
 *      * c(up,left,f)      =   CubeletPosition(up,right,f)
 *      * c(up,right,f)     =   CubeletPosition(up,left,f)
 *      * c(down,left,f)    =   CubeletPosition(down,right,f)
 *      * c(down,right,f)   =   CubeletPosition(down,left,f)
 *
 * */
vecCletPos vecCornerEquPosition(const FaceSide& f);


/** \fn vecCletPos vecCenterEquPosition(const FaceSide& f)
 *  \brief  This function returns a VECtor containing CENTER EQUivalence (Cubelet)POSition of given FaceSide
 *
 * What are center equivalent positions?
 *
 * These are similar to 'edge quivalent position' of a FaceSide except here we consider Center Cubelets
 * present in plane parallel to given FaceSide and passing through central point of Cube.
 * Let p_up be the 'up center equivalent position' of FaceSide f, we write it as
 *
 *      ct(up,f) = p_up
 *
 * Note: For any FaceSide f and x, we have
 *      * ct(x,f)        =   CubeletPosition(x(f))   //For x(f) see setEquivalentFaceSide defined in common.h
 *      * ct(x,front)    =   CubeletPosition(x)
 *
 * Example: List all center equivalent positions of FaceSide f = left
 *      * ct(up,f)       =   CubeletPosition(up)
 *      * ct(left,f)     =   CubeletPosition(back)
 *      * ct(down,f)     =   CubeletPosition(down)
 *      * ct(right,f)    =   CubeletPosition(front)
 *
 */
vecCletPos vecCenterEquPosition(const FaceSide& f);


/** \fn vecCletPos vecMidEdgeEquPos(const FaceSide& f)
 *  /brief  This function returns a VECtor containing MIDdle EDGE EQUivalent (Cubelet)POSitions of given FaceSide
 *
 * What are middle edge equivalent positions?
 *
 * MidEdgeEquPos' are similar to 'edge equivalent position' of a FaceSide except we consider Edge Cubelets
 * present in plane parallel to given FaceSide and passing through central point of Cube.
 * Let p_ul be the '{up,left} middle edge equivalent' of FaceSide f, we write it as
 *
 *      me(up,left,f)   =   p_ul
 *
 * Note: For any FaceSide f, x and y, we have
 *      * me(x,y,f)         =   CubeletPosition(x(f), y(f)) //For x(f) & y(f) see setEquivalentFaceSide defined in common.h
 *      * me(x,y,front)     =   CubeletPosition(x,y)
 *
 * Examlple: List all 'middle edge equivalent positions' of FaceSide f = up
 *      * me(up,left,f)     =   CubeletPosition(back,left)
 *      * me(up,right,f)    =   CubeletPosition(back,right)
 *      * me(down,right,f)  =   CubeletPosition(front,right)
 *      * me(down,left,f)   =   CubeletPosition(front,left)
 *
 */
vecCletPos vecMidEdgeEquPosition(const FaceSide& f);

#endif
