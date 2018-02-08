/*! \file   position.h
 *  \brief  Contains Position class declarations
 *
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#ifndef POSITION_H
#define POSITION_H

#include <vector>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include "common.h"


struct Step;

typedef std::list<Step> StepSequence;


/*! Defines a single Step, the set of parameters we need to specify for rotation of any face
 *
 * */
struct Step
{
    FaceSide f;
    bool is_clockwise;
    std::size_t no_of_turns;
    bool is_mid;


    Step(): f(undefside){}
    //Step(): f(front), is_clockwise(true), no_of_turns(1), is_mid(false){}

    Step(const FaceSide& f): f(f), is_clockwise(true), no_of_turns(1), is_mid(false){}

    Step(const FaceSide& f, std::size_t no_of_turns): f(f), is_clockwise(true), no_of_turns(no_of_turns), is_mid(false){}

    Step(const FaceSide& f, int no_of_turns): f(f), is_clockwise(true), no_of_turns(no_of_turns), is_mid(false){}

    Step(const FaceSide& f, bool is_clockwise): f(f), is_clockwise(is_clockwise), no_of_turns(1), is_mid(false){}

    Step(const FaceSide& f, std::size_t no_of_turns, bool is_clockwise):
        f(f),
        is_clockwise(is_clockwise),
        no_of_turns(no_of_turns),
        is_mid(false){}

    Step(const FaceSide& f, bool is_clockwise, std::size_t no_of_turns):
        f(f),
        is_clockwise(is_clockwise),
        no_of_turns(no_of_turns),
        is_mid(false){}

    Step(const FaceSide& f, bool is_clockwise, std::size_t no_of_turns, bool is_mid):
        f(f),
        is_clockwise(is_clockwise),
        no_of_turns(no_of_turns),
        is_mid(is_mid){}

    friend std::ostream& operator<<(std::ostream &os, Step S);
};


/*! Defines a Positions to refer different parts of Cube
 *
 * A Position can be viewed as an ordered sequence of <i>FaceSide</i>s: 
 *      P = {f<sub>1</sub>, f<sub>2</sub>, f<sub>3</sub>}, where f<sub>i</sub> is a FaceSie.
 *
 * In a valid Position there can be a maximum of three and a minimum of one FaceSide.
 *
 * */
class Position {
    protected:
        
        ///Holds FaceSides
        std::vector<FaceSide> vecSide;
        
        ///Holds PositionType
        PositionType ptype;

    public:
        ///Default constructor
        Position():vecSide{undefside}, ptype(undeftype){};

        ///For initializing any number (1-3) of FaceSides, this constructor is intended to
        ///delegated from other constructors
        Position(const FaceSide first,const FaceSide second = undefside,const FaceSide third = undefside):\
            Position( std::vector<FaceSide>({first,second,third}) ){};
        
        ///Initialization from vector for FaceSides
        Position(const std::vector<FaceSide> _vecSide);

        ///Returns a copy of vecSide
        const std::vector<FaceSide> getSide() const{ return vecSide; }

        ///Returns FaceSide present at 'vecSide[index]'
        FaceSide getSideAt(size_t index) const;
        
        ///Returns pointer to 'ptype'
        PositionType getPositionType() const {return ptype; }

        ///Return true if Position lie on given Face
        bool isOn(const FaceSide& f) const{ return std::find(vecSide.begin(), vecSide.end(), f) != vecSide.end(); }

        ///Number of FaceSides with valid (not undefside) value
        size_t size() const;

        /*! Returns relative Position of this w.r.t. given FaceSide
         *
         * What is relative Position?
         *
         * Relative Position of any Position <i>pos</i> w.r.t. a given FaceSide <i>f</i> is
         * defined as the new Position <i>pos_f</i> that <i>pos</i> would occupy if FaceSide
         * <i>f</i> is brought to front side following standard methods of rotation ( See
         * rotation defined for function setEquivalentFaceSide in common.h ). Let's denote
         * relative Position of <i>pos</i> w.r.t. FaceSide <i>f</i> as rel(pos,f), we can write
         *
         *      rel(pos,f) = pos_f
         *
         * Note: For any Position P = {f1,f2,f3}, where f<i>x</i> is a valid FaceSide
         * and for any arbitrary FaceSide <i>f</i>, we have:
         *
         *      * rel(pos,f) = rel({f1,f2,f3}, f) = { rel(f1,f), rel(f2,f), rel(f3,f) }
         *      * rel(pos,front) = pos
         *
         *
         * Here, rel(FaceSide f,FaceSide g) is the relative orientaion of <i>f</i> w.r.t. <i>g</i>
         * defined in getRelativeFaceSide present in common.h . Above analogy extends to Positions
         * with one and two FaceSides as well.
         *
         * Example: Find relative Position of P(front, left, down) w.r.t right.
         *
         *      rel(P, right)   = rel( {front,left,down}, right )
         *                      = { rel(front,right), rel(left,right), rel(down,right) }
         *                      = { left, back, down }
         *
         * */
        Position getRelativePosition(const FaceSide& f) const;

        /*! Indicate whether the given position would get affected if specified Step is performed.
         * This Steps relate to rotation of faces.
         *
         * */
        bool willGetAffected(Step s) const;

        /*! Returns the updated position, this position would assume if Cube is updated as per
         * specified step sequence using C.update(seq) i.e. when individual Faces are rotated
         * and not necessarily the whole Cube.
         *
         * */
        Position ifRotated(StepSequence seq) const;
        Position ifRotated(Step s) const { StepSequence seq{s}; return ifRotated(seq);}

        ///operator<< overloading to write Position to ostream
        friend std::ostream& operator<<(std::ostream& os, Position P);

        ///Equality
        friend bool operator==(const Position& lhs, const Position& rhs);

        ///Inequality
        friend bool operator!=(const Position& lhs, const Position& rhs){ return !(lhs == rhs); }

        ///Multiplication, modify object
        Position& operator*=(const FaceSide& rhs);

        ///Multiplication, return object copy
        friend Position operator*(Position lhs, const FaceSide& rhs){ lhs *= rhs; return lhs; }

        ///Type operator, converting to size_t to be used as array index later
        operator std::size_t() const;

};


#endif
