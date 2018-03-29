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
typedef std::list<FaceletPosition> listFletPos;
typedef CollectionWrapper<FaceSide,false> CubeletPosition;


/*! \brief Set of Color
 *
 * It can hold a maximum of three Colors, which can be used to refer
 * a Cubelet which have these Colors on its Facelets
 *
 * */
struct SetOfColor{
    SetOfColor(Color c1, Color c2 = undefcol, Color c3 = undefcol);
    SetOfColor(std::vector<Color> vColor);
    Color min() const{ return col_min;};
    Color mid() const{ return col_mid;};
    Color max() const{ return col_max;};
    friend bool operator==(const SetOfColor& lhs, const SetOfColor& rhs){
        return lhs.min() == rhs.min() && lhs.mid() == rhs.mid() && lhs.max() == rhs.max();
    }

    private:
    Color col_min;
    Color col_mid;
    Color col_max;
    void init();
};


///Returns one FaceSide shared by both the CubeletPositions
FaceSide getCommonFace(const CubeletPosition&, const CubeletPosition&);

/*! Return bool suggesting if the given CubeletPositions are located clockwise or not
 *
 * Let's consider the positions P1(front,left,down) and P2(front,left,up). On the front face they
 * are clockwise whereas on left face they are anticlockwise
 *
 * */
bool areClockwise(const CubeletPosition& from, const CubeletPosition& to, const FaceSide& f);


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
        listFletPos getEquivalentFletPosList() const;

        ///Fetch all of Facelets in this Cubelet
        vecFacelet getFacelet() const;

        ///Returns Facelet at given FaceletPositon 
        Facelet getFacelet(const FaceletPosition& fp) const;

        ///Returns Position
        CubeletPosition getPosition() const{ return pos;}

        //Sets Position for cubelet
        void setPosition(const CubeletPosition _pos){ pos = _pos; }

        ///operator<< overloading for writing Cubelet to ostream
        friend std::ostream& operator<<(std::ostream& os, Cubelet C);

        ///Equality
        friend bool operator==(const Cubelet& lhs, const Cubelet& rhs);

        /*! Returns true of both Cubelets have same set of Colors, false other wise
         *
         * */
        friend bool haveSameColors(const Cubelet& lhs, const Cubelet& rhs);

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

};

#endif
