/**
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#ifndef CUBE_H
#define CUBE_H

//Maximum number of visible Cubelets in Cube
#define __MAX_CUB__ 26
//Maximum number of facelets in 3x3 cube
#define __MAX_FAC__ 54

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <unordered_map>
#include "cubelet.h"


typedef std::array<Cubelet, __MAX_CUB__> arrCubelet;
typedef std::array<Facelet, __MAX_FAC__> arrFacelet;


class Cube {
    private:

        ///Array for storing Cubelets with CubeletPosition as key
        arrCubelet aCubelet;

        ///Array for storing Facelets with FaceletPosition as key
        arrFacelet aFacelet;

        ///Auxilliary functions only to be used by the class
        ///Given a FaceSide it return all the FaceletPosition that corresponds that FaceSide
        std::list<FaceletPosition> getFaceletPosition(const FaceSide f);

        ///get all Facelets of a face from std::stream
        void createFace(std::istream &is );

        ///create Cubelets and store in array with help of hashFacelet
        void createCube();

    public:

        ///Default constructor
        Cube(){};

        ///Constructor that takes std::istream and create cubelets
        Cube(std::istream &is);
        
        ///get Facelet located at FaceletPosition specified by three given FaceSides
        Facelet getFacelet(const FaceSide fside1, const FaceSide fside2, const FaceSide fside3) const { return getFacelet( {fside1, fside2, fside3} );}

        ///get Facelet located at FaceletPosition specified by two given FaceSides
        Facelet getFacelet(const FaceSide fside1, const FaceSide fside2) const{ return getFacelet( {fside1, fside2 } ); }

        ///get Facelet located at FaceletPosition
        Facelet getFacelet(const FaceletPosition pos ) const{ return aFacelet.at( pos ) ; }

        ///get Cubelet from CubeletPosition
        Cubelet getCubelet(const CubeletPosition pos) const{ return aCubelet.at( pos ); }

        ///display a given face (position and color)
        void show(const FaceSide& f);

        void rotateLayer(const FaceSide& f, bool is_clockwise = true, bool is_mid = false);

        ///Rotate the given Face of the Cube in clockwise [default] or anticlockwise
        ///fashion as viewed from that (given FaceSide) side
        void rotateSide(const FaceSide& f, bool is_clockwise = true);

        ///Rotate Layer of Cube parallel to given FaceSide and passing through central
        ///point of Cube in clockwise [default] or anti-clockwise fashion as viewed from
        ///given FaceSide.
        void rotateMid(const FaceSide& f, bool is_clockwise = true);

        /// Rotate the Cube clockwise as viewd from specified FaceSide
        void rotate(const FaceSide& f,bool is_clockwise = true);
};

#endif
