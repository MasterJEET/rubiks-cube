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


typedef std::pair<FaceSide, FaceSide> pairFaceSide;
typedef std::unordered_map< pairFaceSide, Facelet > mapFaceletFace;
typedef std::unordered_map<FaceSide, mapFaceletFace> mapFaceletAll;

//Required for using pairFaceSide and FaceSide in std::unordered_map
namespace std {
    template <>
        struct hash<pairFaceSide>{
            size_t operator()(const pairFaceSide& x) const{
                return std::hash<pairFaceSide>()(static_cast<pairFaceSide>(x));
            }
        };

    template <>
        struct hash<FaceSide>{
            size_t operator()(const FaceSide& x) const{
                return std::hash<FaceSide>()(static_cast<FaceSide>(x));
            }
        };
}

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
        Facelet& getFacelet(FaceSide fside1, FaceSide fside2, FaceSide fside3) const;
};

#endif
