/*! \file algobase.h
 *  \brief Provides a base for writing Cube solving algorithms
 *
 *  @author : MasterJEET
 *  @email  : masterjeet9@gmail.com
 *  @date   : 10th Feb 2018
 *
 * */

#ifndef ALGOBASE_H
#define ALGOBASE_H

#include <utility>  //std::pair
#include <list>     //std::list
#include <unordered_map>      //std::unordered_map

#include "cube.h"


/*! This will be used to find relative Position of first FaceletPosition w.r.t. second.
 *
 * Relative position in turn will be used to find sequence of Steps required to bring Facelet
 * at second FaceletPosition to first.
 *
 * */
typedef std::pair<FaceletPosition, FaceletPosition> Relation;

typedef std::pair<CubeletPosition, CubeletPosition> CletRelation;

namespace std {
    template<>
        struct hash<Relation>
        {
            typedef Relation argument_type;
            typedef size_t result_type;

            result_type operator () (const argument_type& x) const
            {
                result_type rt1 = x.first;
                result_type rt2 = x.second;
                return rt1 * 100 + rt2;
            }
        };

    template<>
        struct hash<CletRelation>
        {
            typedef CletRelation argument_type;
            typedef size_t result_type;

            result_type operator () (const argument_type& x) const
            {
                result_type rt1 = x.first;
                result_type rt2 = x.second;
                return rt1 * 100 + rt2;
            }
        };
};

typedef std::unordered_map<Relation, StepSequence> umRelationStep;
typedef std::unordered_map<CletRelation, StepSequence> umCletRelStep;

namespace AlgoBase
{
    /*! Defines basic sequence of Steps to move a Facelet to a new Position.
     *
     * This will mostly be used for solving first Color
     *
     * */
    class Primitive;

    /*! Defines basic query functions for implementing algorithm
     *
     * This will be used to find position of Colors in Cube configuration.
     * Based on the query results algorithm will be built.
     *
     * */
    class Query;
}


class AlgoBase::Primitive
{
    private:
        umRelationStep mRelStep;
        umCletRelStep mCletStep;
        umCletRelStep umCletStepStd;



        /*! Initialize the map with basic movements
         *
         * */
        void init();

        /*! Initialize map to store movements to bring Cubelets to standard initial position
         *
         *  * Standard initial position for a corner Cubelet is {down,back,left}
         *  * Standard initial position for a edge Cubelet is {down,back} or {down,left}
         *
         * */
        void initClet();

    public:
        Primitive();


        /*! Return sequence of movements to be followed if one need to bring FaceSide <i>from</i> to FaceSide <i>to</i>
         *
         * */
        Step howTo(const FaceSide& from, const FaceSide& to);

        /*! Return sequence of steps required to bring Facelet at fp_from to standard destination position.
         *
         * By standard destination position I mean:
         *  * FaceletPosition(front,down,left) for corner Facelets
         *  * FaceletPosition(front,down) for edge Facelets
         *
         * And all movements (steps) mentioned here are defined for rotation of Cube as a whole and not for single face.
         * setting is_mid value is meaningless in such steps.
         *
         * */
        StepSequence getSeqToStandard(FaceletPosition fp_from);


        /*! Returns sequence of Step required to move Cubelet located at P_start to P_end,
         * without affecting any Cubelets located on same FaceSide as P_end except the one located at P_end.
         * 
         * */
        StepSequence getSequence(FaceletPosition P_start, FaceletPosition P_end);


        // Get sequence of Steps required to bring a standard pair of Cubelets to reference orientation.
        // Using methods of rotation for whole Cube and not for a single face
        //
        // What is <i>standard pair</i> of Cubelets?
        //
        // A pair of Cubelets is a <i>standard pair</i> if they have a common face and the Cubelets are not
        // positioned in digonally opposite position on the common face.
        //
        // What is reference orientation for a pair of Cubelets?
        //
        // Reference orientation of Cube for a standard pair of Cubelets, pair(C1,C2), where C1 would be moved to
        // the position of C2 is the orientation where,
        //      * Their common face faces downside,
        //      * C1 is on back and C2 on front FaceSide, and
        //      * Both are on left FaceSide, if they are corner Cubelets.
        //
        // All the primitive sequence of Steps have been defined for reference orientation. Since all the other orientations
        // of Cube can be brought to reference orientation, one can find equivalent movements for all, based on how they can
        // be brought to reference orientation.
        //
        //
        //StepSequence getStepsToReference(const CubeletPosition& from, const CubeletPosition& to);
        

        /*! Retruns rotational reverse sequence for given sequence.
         *
         * What is <i>rotational reverse sequence</i>?
         *
         * If we apply StepSequence seq_org to an initial configuration of Cube to reach a final configuration,
         * than <i>rotational reverse sequence</i> for seq_org is the StepSequence seq_rev which when applied to
         * final Cube configuration yields initial configuration.
         * */
        StepSequence getRotationalReverseSeq(StepSequence seq);
};



class AlgoBase::Query
{
    private:
        Cube& cube;

    public:
        Query(Cube& _cube): cube(_cube){};

        /*! Returns the FaceSide on which the given Color is at center
         *
         * */
        FaceSide center(Color col);
};



#endif //ALGOBASE_H
