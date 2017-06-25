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


typedef std::unordered_map<Position, Facelet> mapFacelet;


class Cube {
    private:

        //Map for storing Facelet with Position as key
        mapFacelet mFacelet;

    public:

        //Default constructor
        Cube();

        //Constructor that takes std::istream and create cubelets
        Cube(std::istream &is);
        
        //get all Facelets of a face from std::stream
        void createFace(std::istream &is);

        //get Facelet at position specified by FaceSide from unordered_map mFacelet, three FaceSides specified
        Facelet getFacelet(const FaceSide fside1, const FaceSide fside2, const FaceSide fside3) const;

        //get Facelet at position specified by FaceSide from unordered_map mFacelet, two FaceSides specified
        Facelet getFacelet(const FaceSide fside1, const FaceSide fside2) const;

        //get Facelet at position specified by FaceSide from unordered_map mFacelet, two FaceSides specified
        Facelet getFacelet(const FaceSide fside1) const;

        //get Facelet from unordered_map mFacelet, where position is specified by Position object
        Facelet getFacelet(const Position pos ) const;
};

#endif
