/*! \file   cube.h
 *  \brief  Contains 'class Cube', this can serve as API for cube solving algorithm
 * 
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#ifndef CUBE_H
#define CUBE_H

///Number of visible Cubelets in 3x3x3 Cube
#define __NUM_CUBELET__     26
///Number of facelets in 3x3x3 cube
#define __NUM_FACELET__     54
///Maximum number of FaceSide or Color required to specify a Facelet or Cubelet
#define __NUM_REQUIRED__    3

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>    //std::find
#include <iterator>     //std::begin, std::end
#include "cubelet.h"

typedef std::array<Cubelet, __NUM_CUBELET__> arrCubelet;
typedef std::array<CubeletPosition, __NUM_CUBELET__> arrCubeletPosition;
typedef std::array<Facelet, __NUM_FACELET__> arrFacelet;
typedef std::array<std::size_t, __NUM_FACE__> arrNumber;
typedef std::array<bool, __NUM_FACE__> arrBool;
typedef std::array<Color, __NUM_FACE__> arrColor;
typedef std::array<FaceSide, __NUM_FACE__> arrFaceSide;
typedef std::list<FaceletPosition> lFletPos;


namespace AlgoBase {
    class Query;
};

class Cube;


/*! \brief For listing out different input format for Cube
 *
 * */
enum enInputFormat {
    LINEAR_FORMAT,
    STEP_FORMAT
};


template <bool _isFaceletType>
class CollectionWrapper<Color, _isFaceletType> : public CollectionChild<Color, _isFaceletType>
{

    Cube *pCube;

    public:
    CollectionWrapper( Cube* p, Color c1 = undefcol, Color c2 = undefcol, Color c3 = undefcol ):
        CollectionChild<Color, _isFaceletType>( c1, c2, c3 ), pCube(p)
    {}

    bool are_opposite(Color c1, Color c2) const;
    bool any_opposite(Color c1, Color c2, Color c3) const;
};


/*! Generic interface for collection
 *
 * */
struct Collection {
    template<typename E, bool _isFaceletType> Collection(
            E _first    = upper_limit<E>(),
            E _second   = upper_limit<E>(),
            E _third    = upper_limit<E>()
            ):
        pbase( new CollectionChild<E,_isFaceletType> (_first, _second, _third) )
    {};

    operator std::size_t() const { return (std::size_t)(*pbase); }

    private:
    CollectionBase::ptr pbase;
};



class Cube {
    private:

        /*! Array for storing Cubelets with CubeletPosition as key
         *
         * */
        arrCubelet aCubelet;

        /*! Array for storing opposite Color
         *
         * */
        arrColor aOppColor;

        /*! This array contains mapping between SetOfColor and the CubeletPosition.
         * This is a class invariant.
         *
         * */
        arrCubeletPosition aCletPos;

        /*! vector for mapping of NUMBER -> CBUELET POSITION,
         * Given an integer it stores which CubeletPostion int refers to
         *
         * */
        static vecCletPos vCletPos;
        static bool is_vCletPos_set;

        /*! vector for mapping of NUMBER -> FACELET POSITION,
         * Given an integer it stores which FaceletPostion int refers to
         *
         * */
        static vecFletPos vFletPos;
        static bool is_vFletPos_set;

        /*! vector for mapping of NUMBER -> COLOR,
         * Given an integer it stores which Color int refers to
         *
         * */
        static std::vector<Color> vCol;
        static bool is_vCol_set;

        /*! vector containing mapping between NUMBER --> FaceSide
         * Given and integer, idx: 0 <= idx < __NUM_FACE__, stores which FaceSide idx refers to
         *
         * */
        static std::vector<FaceSide> vFS;
        static bool is_vFS_set;

        /*! Number of instances of Cube created
         *
         * */
        static std::size_t num_of_instances;

        /*! Make inverse mapping for CubeletPositions.
         *
         * All CubeletPositions are associated with an integer (key) by
         * operator(). This function takes that integer and use it as index
         * for inserting CubeletPosition to a vector
         *
         * */
        static void mapIntToCubeletPosition();

        /*! Make inverse mapping for FaceletPositions.
         *
         * All FaceletPositions are associated with an integer (key) by
         * operator(). This function takes that integer and use it as index
         * for inserting FaceletPosition to a vector
         *
         * */
        static void mapIntToFaceletPosition();

        /*! Make inverse mapping for Color.
         *
         * All Colors are associated with an integer (key) as they
         * are elements of an Enum. This function takes that integer and use it as index
         * for inserting Color to a vector
         *
         * */
        static void mapIntToColor(){ vCol = ::elements<Color>(); is_vCol_set = true;}

        /*! Make inverse mapping of FaceSide
         *
         * All FaceSides ae associated with an integer (key) as they
         * are elements of an Enum. This function takes that integer and use it as index
         * for inserting FaceSide to a vector
         *
         * */
        static void mapIntToFaceSide(){ vFS = ::elements<FaceSide>(); is_vFS_set = true;}

        ///Initialize the cube, constructors will call this init method
        void init(std::istream &is, enInputFormat eifX);

        /*! Validate Color on edge Cubelets
         *
         * Check that no Facelets of any edge Cubelet have same or opposite Color
         * (see cuception.h for definition of opposite Color)
         *
         * */
        void validateEdgeColor(vecFacelet& vFacelet);


        /*! Validate Color on corner Cubelets
         *
         * Check that no two Facelets of any corner Cubelet have same or opposite Color
         *
         * */
        void validateCornerColor(vecFacelet& vFacelet);


        /*! Check if number of Colors are assigned to different position types, correct number of times
         *
         * */
        void validateNumOfColor(
                arrNumber& aNumOfCenterCol,
                arrNumber& aNumOfEdgeCol,
                arrNumber& aNumOfCornerCol
                );

        ///get all Facelets of a face from std::stream of step input
        void createFaceFromStepInput(
                std::istream &is,
                vecFacelet& vFacelet,
                arrNumber& aNumOfCenterCol,
                arrNumber& aNumOfEdgeCol,
                arrNumber& aNumOfCornerCol
                );

        ///get all Facelets of a face from std::stream of linear input
        void createFaceFromLinearInput(
                std::istream &is,
                vecFacelet& vFacelet,
                arrNumber& aNumOfCenterCol,
                arrNumber& aNumOfEdgeCol,
                arrNumber& aNumOfCornerCol
                );

        /*! Find opposite Color
         *
         * Set figure out opposite Color for each Color i.e. let's say we have a Color red
         * in Center Cubelet of Front side, what is the color on Back (opposite of Front) side
         *
         * */
        void setOppColor(vecFacelet& vFacelet);

        ///create Cubelets and store in array with help of vecFacelet
        void createCube(vecFacelet& vFacelet);

        /*! Auxiliary function to be called from rotateLayer
         *
         * */
        void helper(const CubeletPosition& cp, FaceSide f, std::size_t n = 1);


        /*! Rotate any specified layer of Cube
         *
         * rotate any layer of cube, side [default] or middle (as per is_mid), parallel to any FaceSide
         * (specified by FaceSide) and in clockwise [default] or anti-clockwise (as per is_clockwise)
         * fashion as viewd from specified FaceSide
         *
         * */
        void rotateLayer(
                const FaceSide& f,
                bool is_clockwise = true,
                std::size_t no_of_turns = 1,
                bool is_mid = false
                );

    public:

        ///Default constructor
        Cube();

        ///Constructor that takes std::istream and create cubelets
        Cube(std::istream &is, enInputFormat eifX = LINEAR_FORMAT);

        ///Construct cube from file (filepath provided)
        Cube(std::string file_path, enInputFormat eifX = LINEAR_FORMAT);
        
        ///get Facelet located at FaceletPosition specified by three given FaceSides
        Facelet getFacelet(const FaceSide fs1, const FaceSide fs2, const FaceSide fs3) const {
            return getFacelet( {fs1, fs2, fs3} );
        }

        ///get Facelet located at FaceletPosition specified by two given FaceSides
        Facelet getFacelet(const FaceSide fs1, const FaceSide fs2) const{
            return getFacelet( {fs1, fs2 } );
        }

        ///get Facelet located at FaceletPosition
        Facelet getFacelet(const FaceletPosition pos ) const {
            return aCubelet.at( CubeletPosition (pos.all()) ).getFacelet(pos) ;
        }

        ///get corner Cubelet
        Cubelet getCubelet(const FaceSide& f1, const FaceSide& f2, const FaceSide& f3) const{
            return getCubelet(CubeletPosition(f1,f2,f3));
        }

        ///get edge Cubelet
        Cubelet getCubelet(const FaceSide& f1, const FaceSide& f2) const{
            return getCubelet({f1,f2});
        }

        ///get Cubelet from three Colors
        Cubelet getCubelet(const Color& c1, const Color& c2, const Color& c3) const{
            return getCubelet({c1, c2, c3});
        }

        ///get Cubelet from two Colors
        Cubelet getCubelet(const Color& c1, const Color& c2) const{
            return getCubelet({c1, c2});
        }

        ///get Cubelet from ColorSet
        Cubelet getCubelet(const SetOfColor& cs) const{
            return getCubelet( aCletPos.at( ColorSetToInt(cs) ) );
        }

        ///get Cubelet from CubeletPosition
        Cubelet getCubelet(const CubeletPosition pos) const{ return aCubelet.at( pos ); }

        ///Given an interger between 0 - 25, return corresponding CubeletPosition
        static CubeletPosition getCubeletPosition(std::size_t index);

        ///Given an interger between 0 - 53, return corresponding FaceletPosition
        static FaceletPosition getFaceletPosition(std::size_t index);

        ///Given an integer between 0 - 5, return associated Color
        static Color getColorFromInt(std::size_t index);

        ///Get list of FaceletPositions associated with give CubeletPosition
        static lFletPos getFaceletPositions(CubeletPosition cp);

        /*! Check if two Colors are opposite
         *
         * Retuns true if Colors are opposite, else false. When first Color is not defined, returns false.
         * See cuception.h for definition of opposite Color.
         *
         * */
        bool areOppColor(const Color& first, const Color& second) const;

        /*! Check if any two of given three Colors are opposite
         *
         * Retuns true if Colors are opposite, else false.
         * If first or second Color is not defined, then also returns false.
         * See cuception.h for definition of opposite Color.
         *
         * */
        bool anyOppColor(const Color& first, const Color& second, const Color& third) const;


        //! Return the side where given Color is present at center
        //
        //
        //FaceSide getSideOfColor(const Color& c);


        /*! Map each SetOfColor to an int
         *
         * The purpose of this mapping is, with this every combination of three or less Colors
         * can be associated with an integer. This integer can be used as a key for array
         * of CubeletPositions, effectively we'll have one-to-one correspondence between
         * set of three or less Colors and CubeletPositions.
         * */
        std::size_t ColorSetToInt(const SetOfColor& cs) const;
        std::size_t ColorSetToInt(const CubeletPosition& cp) const;
        std::size_t ColorSetToInt(const Color& c1, const Color& c2)const {return ColorSetToInt({c1,c2});};
        std::size_t ColorSetToInt(const Color& c1, const Color& c2, const Color& c3) const{
            return ColorSetToInt({c1,c2,c3});
        }


        // Set equivalent Colors
        //
        // What are equivalent Colors?
        //
        // For a Color <i>col</i> which is located at center of FaceSide <i>f</i>, and for an arbitrary
        // FaceSide <i>x</i>; we define <i>x</i> equivalence of <i>col</i>, x(col), as:
        //
        //      x(col) = center_color( x(f) )
        //
        // where center_color(FaceSide) is Color located at center of given FaceSide. For definition of
        // of <i>x equivalence of f</i> i.e. x(f), see setEquivalentFaceSide declared in common.h .
        //
        // Let's say red Color is at the center of top face. Right face is right equivalent of up,
        // let's say yellow Color is at the center of right face. Then right equivalent of red Color
        // would be yellow:
        //
        //      col = red, f = up, x = right
        //      Now x(col)  = center_color( x(f) )
        //      =>  right(red) = center_color( right(up) ) = center_color( right )
        //      =>  right(red) = yellow
        //
        // This function sets up, right, down & left equivalent Color of cFront to
        // cUp, cRight, cDown & cLeft respectively.
        //
        //
        //void setEquivalentColor(
        //        const Color& cFront,
        //        Color& cUp,
        //        Color& cRight,
        //        Color& cDown,
        //        Color& cLeft
        //        );


        //display a given face (position and color)
        //void show(const FaceSide& f);


        /*! Rotate any specified side of Cube
         *
         * Rotate the given Face of the Cube in clockwise [default] or anticlockwise
         * fashion as viewed from that (given FaceSide) side
         *
         */
        void rotateSide();
        void rotateSide(const FaceSide& f);
        void rotateSide(const FaceSide& f, std::size_t no_of_turns);
        void rotateSide(const FaceSide& f, int no_of_turns);
        void rotateSide(const FaceSide& f, bool is_clockwise);
        void rotateSide(const FaceSide& f, bool is_clockwise, std::size_t no_of_turns);
        void rotateSide(const FaceSide& f, std::size_t no_of_turns, bool is_clockwise);
        void rotateSide(Step s);


        /*! Rotate any specified middle layer of Cube
         *
         * Rotate Mid Layer of Cube ( parallel to given FaceSide and passing through central
         * point of Cube ) in clockwise [default] or anti-clockwise fashion as viewed from
         * given FaceSide.
         *
         */
        void rotateMid();
        void rotateMid(const FaceSide& f);
        void rotateMid(const FaceSide& f, std::size_t no_of_turns);
        void rotateMid(const FaceSide& f, int no_of_turns);
        void rotateMid(const FaceSide& f, bool is_clockwise);
        void rotateMid(const FaceSide& f, std::size_t no_of_turns, bool is_clockwise);
        void rotateMid(const FaceSide& f, bool is_clockwise, std::size_t no_of_turns);
        void rotateMid(Step s);


        /*! Rotate the Cube 
         *
         * Let 1 & 2 denotes the state of Cube before & after the operation. With usual notation of
         *
         *      F: Front,   B: Back,    U: Up
         *      D: Down,    L: Left,    R: Right
         *
         * If operated with FaceSide Up on Cube with is_clockwise set to true(default behaviour),
         * Up and Down Faces remain at their place.
         * Front FaceSide turns to Left, Left turns to Back and so on.
         *
         *      1U -> 2U,   1D -> 2D,   1F -> 2L
         *      1R -> 2F,   1B -> 2R,   1L -> 2B
         *
         */
        void rotate();
        void rotate(const FaceSide& f);
        void rotate(const FaceSide& f, std::size_t no_of_turns);
        void rotate(const FaceSide& f, int no_of_turns);
        void rotate(const FaceSide& f, bool is_clockwise);
        void rotate(const FaceSide& f, std::size_t no_of_turns, bool is_clockwise);
        void rotate(const FaceSide& f, bool is_clockwise, std::size_t no_of_turns);
        void rotate(Step s);
        void rotate(StepSequence seq);

        /*! Update the cube by rotating its FaceSides as specified in StepSequence
         *
         * */
        void update(StepSequence s);

        /*! Making FaceletColor a friend
         *
         * */
        friend class FaceletColor;

        /*! Making Query class a friend
         *
         * Query class will address basic queries that will arise while solving Cube
         * and might require access to Cube's private attributes.
         *
         * */
        friend class AlgoBase::Query;

        /*! Making CollectionWrapper<Color,bool> a friend.
         * partially specialized template classes are tough to make friend due to weired syntax.
         *
         * */
        template <typename E,bool _isFaceletType> friend class CollectionWrapper;
};



/*! \fn std::list<FaceletPosition> getEquivalentFletPos(const FaceSide f)
 *  \brief  Fetch list of FaceletPositions associated with a given FaceSide
 *  <pre>
 *                U U U
 *                U U U
 *                U U U
 *          L L L F F F R R R B B B      1 2 3 #
 *          L L L F F F R R R B B B      4 5 6 # This is the sequence
 *          L L L F F F R R R B B B      7 8 9 #
 *                D D D
 *                D D D
 *                D D D
 *                </pre>
 * Returns above positions for a face,
 * Order of positions in the list is depicted by above diagram
 *
 * */
listFletPos getEquivalentFletPos(const FaceSide f);




/*! \fn template <typename P> std::vector<P> vecEdgeEquivalence(const FaceSide& f);
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
 *      * e(x,f) = Position( x(f), f ) //where x(f) is x FaceSide equivalence of f, defined in common.h
 *      * e(x,front) = Position( x(front), front) = Position(x,front) //Since x(front) = x
 *
 * Example: consider listing all edge equivalence of FaceSide f = down
 *      * e(up,f)       =   Position(f,front)
 *      * e(right,f)    =   Position(f,right)
 *      * e(down,f)     =   Position(f,back)
 *      * e(left,f)     =   Position(f,left)
 *
 * */
template <typename P> std::vector<P> vecEdgeEquivalence(const FaceSide& f);



/*! \fn template <typename P> std::vector<P> vecCornerEquivalence(const FaceSide& f)
 *  \brief  This function returns (a vector of) corner Position equivalence of FaceSide 'f'.
 *  Order of equivalence returned: {up,left}, {up,right}, {down,right}, {down,left}
 *
 * What are corner equivalent Positions?
 *
 * Similar to edge equivalent Positions but here we consider corner Cubelets and their Positions, instead of Edges.
 * Let Position p_ul be "{up,left} corner equivalent position" of FaceSide f. Let's write it as
 *
 *      c(up,left,f) = p_ul
 *
 * Note: For any FaceSide f, x and y we have
 *      * c(x,y,f)  =   Position(x(f), y(f), f) //For x(f) & y(f), see setEquivalentFaceSide defined in common.h
 *      * c(x,y,front)  = Position(x,y,front)
 *
 * Example: list all corner equivalent Positions of FaceSide f = back
 *      * c(up,left,f)      =   Position(f,up,right)
 *      * c(up,right,f)     =   Position(f,up,left)
 *      * c(down,left,f)    =   Position(f,down,right)
 *      * c(down,right,f)   =   Position(f,down,left)
 *
 * */
template <typename P> std::vector<P> vecCornerEquivalence(const FaceSide& f);



/** \fn template <typename P> std::vector<T> vecCenterEquivalence(const FaceSide& f)
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
 *      * ct(x,f)        =   Position(x(f))   //For x(f) see setEquivalentFaceSide defined in common.h
 *      * ct(x,front)    =   Position(x)
 *
 * Example: List all center equivalent positions of FaceSide f = left
 *      * ct(up,f)       =   Position(up)
 *      * ct(left,f)     =   Position(back)
 *      * ct(down,f)     =   Position(down)
 *      * ct(right,f)    =   Position(front)
 *
 */
template <typename P> std::vector<P> vecCenterEquivalence(const FaceSide& f);



/** \fn template <typename P> std::vector<P> vecMidEdgeEquivalence(const FaceSide& f)
 *  \brief  This function returns a VECtor containing MIDdle EDGE EQUivalent (Cubelet)POSitions of given FaceSide
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
 *      * me(x,y,f)         =   Position(x(f), y(f)) //For x(f) & y(f) see setEquivalentFaceSide defined in common.h
 *      * me(x,y,front)     =   Position(x,y)
 *
 * Examlple: List all 'middle edge equivalent positions' of FaceSide f = up
 *      * me(up,left,f)     =   Position(back,left)
 *      * me(up,right,f)    =   Position(back,right)
 *      * me(down,right,f)  =   Position(front,right)
 *      * me(down,left,f)   =   Position(front,left)
 *
 */
template <typename P> std::vector<P> vecMidEdgeEquivalence(const FaceSide& f);


#endif
