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
#include <map>
#include <utility>
#include "Cubelet.h"

typedef std::pair<FaceSide, FaceSide> pairFaceSide;
typedef std::map< pairFaceSide, Facelet > mapFaceletFace;
typedef std::map<FaceSide, mapFaceletFace> mapFaceletAll;

class Cube {
    private:

        //Stores vector of Cubelets for a given cube
        std::vector<Cubelet> vecCubelet;

        //Map for storing Facelet for all position of cubes
        mapFaceletAll mFaceletAll;

    public:

        //Default constructor
        Cube();

        //Constructor that takes std::istream and create cubelets
        Cube(std::istream &is);
        
        //get all Facelets of a face from std::stream
        void createFace(std::istream &is);

        //get Facelet at position specified by FaceSide
        Facelet &getFacelet(FaceSide fside1, FaceSide fside2, FaceSide fside3) const;
};

#endif
