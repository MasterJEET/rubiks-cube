/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include "cubelet.h"


typedef std::unordered_map<CubeletPosition, Cubelet> hashCubelet;


class Cube {
    private:

        //Map for storing pointers to Cubelets with Position as key
        hashCubelet hCubelet;

    public:

        //Default constructor
        Cube(){};

        //Constructor that takes std::istream and create cubelets
        Cube(std::istream &is);
        
        //get all Facelets of a face from std::stream
        void createFace(std::istream &is, hashFacelet& hFacelet);

        //get Facelet at position specified by FaceSide from unordered_map hCubelet, three FaceSides specified
        Facelet getFacelet(const FaceSide fside1, const FaceSide fside2, const FaceSide fside3) const { return getFacelet( {fside1, fside2, fside3} );}

        //get Facelet at position specified by FaceSide from unordered_map hCubelet, two FaceSides specified
        Facelet getFacelet(const FaceSide fside1, const FaceSide fside2) const{ return getFacelet( {fside1, fside2 } ); }

        //get Facelet from unordered_map hCubelet, where position is specified by FaceletPosition object
        Facelet getFacelet(const FaceletPosition pos ) const{ return hCubelet.at( pos ).getFacelet( pos )   ; }

        //create Cubelets and store in map with help of hashFacelet
        void createCubelet(hashFacelet& hFacelet);

        //get Cubelet from Position
        Cubelet getCubelet(const CubeletPosition pos) const{ return hCubelet.at( pos ); }

        //Cube multiplication with a FaceSide
        Cube& operator*=(const FaceSide& rhs);
};

#endif
