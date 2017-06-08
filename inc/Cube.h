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
#include "Cubelet.h"

class Cube {
    private:

        //Stores vector of Cubelets for a given cube
        std::vector<Cubelet> vecCubelet;

    public:

        //Default constructor
        Cube();

        //Constructor that takes std::istream and create cubelets
        Cube(std::istream &is);
        
        //get all Facelets of a face from std::stream
        void getFace(std::istream &is);
};

#endif
