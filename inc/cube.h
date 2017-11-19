/**
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <unordered_map>
#include "cubelet.h"


typedef std::unordered_map<CubeletPosition, Cubelet> hashCubelet;


class Cube {
    private:

        ///Map for storing pointers to Cubelets with Position as key
        hashCubelet hCubelet;

        ///Auxilliary functions only to be used by the class
        ///Given a FaceSide it return all the FaceletPosition that corresponds that FaceSide
        std::list<FaceletPosition> getFaceletPosition(const FaceSide f);

    public:

        ///Default constructor
        Cube(){};

        ///Constructor that takes std::istream and create cubelets
        Cube(std::istream &is);
        
        ///get all Facelets of a face from std::stream
        void createFace(std::istream &is );

        ///get Facelet at position specified by FaceSide from unordered_map hCubelet, three FaceSides specified
        Facelet getFacelet(const FaceSide fside1, const FaceSide fside2, const FaceSide fside3) const { return getFacelet( {fside1, fside2, fside3} );}

        ///get Facelet at position specified by FaceSide from unordered_map hCubelet, two FaceSides specified
        Facelet getFacelet(const FaceSide fside1, const FaceSide fside2) const{ return getFacelet( {fside1, fside2 } ); }

        ///get Facelet from unordered_map hCubelet, where position is specified by FaceletPosition object
        Facelet getFacelet(const FaceletPosition pos ) const{ return hCubelet.at( pos ).getFacelet( pos )   ; }

        ///create Cubelets and store in map with help of hashFacelet
        void createCube();

        ///get Cubelet from Position
        Cubelet getCubelet(const CubeletPosition pos) const{ return hCubelet.at( pos ); }

        ///display a given face (position and color)
        void show(const FaceSide f);

        /** Turn the Cube anti-clockwise w.r.t axis (& sense of rotation) specified by FaceSide
         *
         * Let 1 & 2 denotes the state of Cube before & after the operation. With usual notation of
         * - F: Front
         * - B: Back
         * - U: Up
         * - D: Down
         * - L: Left
         * - R: Right
         *
         * If operated with FaceSide Up on Cube, turn the Cube so that Up and Down Faces remain at their place. Front FaceSide turns to Right, Right turns to Back and so on.
         * - 1U -> 2U
         * - 1D -> 2D
         * - 1F -> 2R
         * - 1R -> 2B
         * - 1B -> 2L
         * - 1L -> 2F
         *
         */
        Cube& operator*=(const FaceSide& rhs);
};

#endif
