/*! \file   cuceptions.h
 *  \brief  Contains custom exceptions to be used in 'class Cube' (CUbe exCEPTIONS)
 * 
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Jan 2018
 *
 * There are seven primitive checks done for input validation as listed below.
 * For most of the checks, exceptions declared in this file are thrown.
 *
 *  1. A Total of six listed Colors are allowed.
 *  2. Each Color can occur exactly 9 times i.e. a Color can be assigned to
 *     exactly 9 Facelets (Cubelets).
 *  3. Each Color must be assigned to single center Facelet, eqauivalently
 *     all centerpiece must have unique Color.
 *  4. Each Color can be assigned to exactly 4 edge pieces.
 *  5. Each Color can be assigned to exactly 4 corner pieces.
 *  6. No two Colors on any edge Cubelet should have same or opposite Color.
 *  7. No two Colors of any corner Cubelet should have same or opposite Color.
 *
 *
 * Opposite Color
 *
 *  Let's say a Color 'cf' is at center of certain FaceSide (say Front) and
 *  let 'cb' be at the center of opposite FaceSide (here Back) then we say
 *  Colors 'cf' and 'cb' are each other's opposite Color.
 *
 * */


#ifndef CUCEPTIONS
#define CUCEPTIONS

#include <stdexcept>        //std::runtime_error
#include <sstream>          //std::ostringsream
#include <cube.h>           //Facelet

typedef std::vector<Facelet> vecFacelet;

class NumOfFaceletsException : public std::runtime_error {
    private:

        ///Message to be printed when exception occurs
        static std::ostringstream msg;  

        ///Index of vFacelet where Facelet is not initialized using input
        std::size_t index;

    public:

        NumOfFaceletsException(std::size_t index);

        ///returns custom message to be printed when exception is invoked
        virtual const char* what() const throw();

};


class NumOfColorsException : public std::runtime_error {
    private:
        ///Message to be printed when exception occurs
        static std::ostringstream msg;

        ///Index of Color which occurred more or less than 9 times
        std::size_t index;

        ///Number of occurence of this Color
        std::size_t count;

    public:

        NumOfColorsException(std::size_t _index, std::size_t _count);

        virtual const char* what() const throw();

};


class NumOfCenterColorException : public std::runtime_error {
    private:
        ///Message to be printed when exceptions occurs
        static std::ostringstream msg;

        ///Index of Centerpiece Color which occured more or less than once
        std::size_t index;

        ///Number of occurences fo this Color
        std::size_t count;

    public:

        NumOfCenterColorException(std::size_t _index, std::size_t _count);

        virtual const char* what() const throw();
};


///To be thrown when Colors on an edge piece are same i.e.
///when check number 6 fails.
class SameEdgeColorException : public std::runtime_error {
    private:
        static std::ostringstream msg;
        std::vector<FaceSide> vFS;

    public:
        SameEdgeColorException(std::vector<FaceSide> _vFS);
        virtual const char* what() const throw();
};


///To be thrown when Colors on an edge piece are opposite i.e.
///when check number 6 fails.
class OppositeEdgeColorException : public std::runtime_error {
    private:
        static std::ostringstream msg;
        std::vector<FaceSide> vFS;

    public:
        OppositeEdgeColorException(std::vector<FaceSide> _vFS);
        virtual const char* what() const throw();
};


///To be thrown when Colors on an corner piece are same i.e.
///when check number 7 fails.
class SameCornerColorException : public std::runtime_error {
    private:
        static std::ostringstream msg;
        CubeletPosition cp;

    public:
        SameCornerColorException(CubeletPosition _cp);
        virtual const char* what() const throw();
};


///To be thrown when Colors on an corner piece are opposite i.e.
///when check number 7 fails.
class OppositeCornerColorException : public std::runtime_error {
    private:
        static std::ostringstream msg;
        CubeletPosition cp;

    public:
        OppositeCornerColorException(CubeletPosition _cp);
        virtual const char* what() const throw();
};


#endif
