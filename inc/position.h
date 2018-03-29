/*! \file   position.h
 *  \brief  Contains class Collection
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
#include <memory>       //std::unique_ptr
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



/*! \fn template <typename E> upper_limit()
 *  \brief  This functions returns an object of type E which when used for comparison using operator '<',
 *  always yields true.
 *
 *  Example: Let's say we have
 *          E var1();
 *          E var2 = AlgoBase<E>::upper_limit(); then
 *          var1 < var2; evaluates to true always
 *
 * */
template <typename E> E upper_limit();


/*! Abstract base class for Collection
 *
 * */
struct CollectionBase {
    using ptr = std::unique_ptr< CollectionBase >;

    /*! Returns unique integer associated with each collection.
     *
     * */
    virtual operator std::size_t() const = 0;
};


template <typename E, bool B>
class CollectionChild;


template <typename E, bool B>
bool operator==(const CollectionChild<E,B>& lhs, const CollectionChild<E,B>& rhs);

template <typename E, bool B>
bool operator!=(const CollectionChild<E,B>& lhs, const CollectionChild<E,B>& rhs)
{ return !(lhs==rhs); }


template <typename E, bool B>
class CollectionChild : public CollectionBase {

    /*! bool indicating whether this class is Facelet type or Cubelet type (see definition here)
     *
     * */
    bool isFaceletType;

    virtual bool any_same(E e1, E e2, E e3) const { return (e1==e2) || (e2==e3) || (e3==e1); }

    protected:
    E _first;
    E _second;
    E _third;

    /*! Number of valid elements. All elements except returned by upper_limit<E>() are
     * regarded as valid elements.
     *
     * */
    std::size_t _num;

    virtual bool are_opposite(E e1, E e2) const = 0;
    virtual bool any_opposite(E e1, E e2, E e3) const = 0;
    friend bool operator== <>(const CollectionChild<E,B>& lhs, const CollectionChild<E,B>& rhs);

    public:
    CollectionChild (E e1 = upper_limit<E>(), E e2 = upper_limit<E>(), E e3 = upper_limit<E>());
    CollectionChild (std::vector<E>);

    /*! This assigns a unique positive integer to each unique Collection
     *
     * Uniqueness is defined by first element and set of last tow[optional] elements.
     * Let N ( 0 <= N <=3 ) be the total number of elements defined in this Collection.
     * Two Collections with N1 and N2 number of defined elements are
     * identical if and only if N1 = N2 and following holds:
     *      * if N1 = N2 = 1: then single element of both Collection must match
     *      * if N1 = N2 = 2: If _isFaceletType is true, both the elements must match in
     *      ordered sequence i.e. first element of Collection1 must match with first element
     *      of Collection2 and similary second element of both must match. If _isFaceletType
     *      is false, order of two elements don't matter i.e. two should form indentical set.
     *      * if N1 = N2 = 3: If _isFaceletType is true, first element of both must match,
     *      second and third element of Collection1 & 2 must form identical set.
     *      If _isFaceletType = false, three elements form each Collection must form identical set.
     *
     * Example (_isFaceletType = true):
     *      * {orange} & {orange,yellow} are unique or different.
     *      * {red} & {green} are unique.
     *      * {white, yellow} & {yellow, white} are unique.
     *      * {white, yellow} & {white, undefcol, yellow} are identical. Note there are only two
     *      defined Colors on second Collection.
     *      * {white,red,green} & {white,green,red} are identical.
     *      * {white,red,green} & {white,red,blue} are unique.
     *
     * Example (_isFaceletType = false):
     *      * {up} & {up} are unique or different.
     *      * {front} & {front,up} are unique.
     *      * {right,down} & {down,right} are not unique. They are identical.
     *      * {right,down} & {undefside,down,right} are identical.
     *      * {front,up,left} & {up,front,left} are identical.
     *      * {front,up,left} & {front,up,right} are unique.
     *
     * A valid Collection:
     *      -# have at least one element defined,
     *      -# doesn't contain opposite or same elements,
     *      -# have first element always defined.
     *
     * All unique valid Collections are assigned unique positive integer within the range [0, max)
     * and all non-valid Collections are assigned -1. Note here that the 'max' is not inclusive.
     * The 'max' value is __NUM_FACELET__ i.e. 54 if _isFaceletType is true and __NUM_CUBELET__
     * i.e. 26 if _isFaceletType is false.
     *
     * */
    virtual operator std::size_t() const;

    E first() const{return _first;}
    E second() const{return _second;}
    E third() const{return _third;}
    std::size_t num() const{return _num;}
    std::vector<E> all() const{ return std::vector<E>({_first,_second,_third}); }
};


template <typename E, bool _isFaceletType>
class CollectionWrapper : public CollectionChild<E, _isFaceletType> {};

template <bool B>
std::ostream& operator<<(std::ostream& os, CollectionWrapper<FaceSide,B>);

template <bool _isFaceletType>
class CollectionWrapper<FaceSide, _isFaceletType> : public CollectionChild<FaceSide, _isFaceletType>
{
    private:
        PositionType _ptype;
        FaceSide& _first;
        FaceSide& _second;
        FaceSide& _third;
        std::size_t& _num;

    public:
        CollectionWrapper(std::vector<FaceSide>);

        CollectionWrapper(FaceSide f1 = undefside, FaceSide f2 = undefside, FaceSide f3 = undefside):
            CollectionWrapper( std::vector<FaceSide>({f1,f2,f3}) ){}

        CollectionWrapper(const CollectionWrapper<FaceSide,_isFaceletType>&);

        CollectionWrapper<FaceSide, _isFaceletType>& operator=(CollectionWrapper<FaceSide,_isFaceletType>);

        bool are_opposite( FaceSide f1, FaceSide f2) const
        { return areOpposite(f1,f2); }

        bool any_opposite( FaceSide f1, FaceSide f2, FaceSide f3) const
        { return anyOpposite(f1,f2,f3); }

        PositionType ptype() const {return _ptype;}

        /*! Return true if Position(_first,_second,_third) lie on given FaceSide f
         *
         * */
        bool isOn(const FaceSide& f) const
        { return (f!=undefside) && (f==_first || f==_second || f==_third); }

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
        CollectionWrapper<FaceSide,_isFaceletType> relative(const FaceSide& f) const;

        /*! Indicate whether the given position would get affected if specified Step is performed.
         * This Steps relate to rotation of faces.
         *
         * */
        bool affectable(Step s) const;

        /*! Returns result i.e. updated position, this position would assume if Cube is updated as per
         * specified step sequence using C.update(seq) i.e. when individual Faces are rotated
         * and not necessarily the whole Cube.
         *
         * */
        CollectionWrapper<FaceSide,_isFaceletType> result(StepSequence seq) const;
        CollectionWrapper<FaceSide,_isFaceletType> result(Step s) const { StepSequence seq{s}; return result(seq);}

        friend std::ostream& operator<< <>(std::ostream& os, CollectionWrapper<FaceSide,_isFaceletType>);

        CollectionWrapper<FaceSide,_isFaceletType>& operator*=(const FaceSide& rhs);
        friend CollectionWrapper<FaceSide,_isFaceletType> operator*(CollectionWrapper<FaceSide,_isFaceletType> lhs, const FaceSide& rhs)
        { lhs *= rhs; return lhs; }
};

#endif
