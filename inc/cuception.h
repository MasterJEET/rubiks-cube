/*! \file   cuception.h
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
 *  2. Each Color must be assigned to single center Facelet, eqauivalently
 *     all centerpiece must have unique Color.
 *  3. Each Color can be assigned to exactly 4 edge pieces.
 *  4. Each Color can be assigned to exactly 4 corner pieces.
 *  5. No two Colors on any edge Cubelet should have same or opposite Color.
 *  6. No two Colors of any corner Cubelet should have same or opposite Color.
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


class Cuception : public std::runtime_error {
    protected:
        ///Custom message holder
        static std::string message;
    public:
        Cuception();
        Cuception(std::string str);
};


class NumOfFaceletException : public Cuception {
    protected:

        ///Index of vFacelet where Facelet is not initialized using input
        std::size_t index;

    public:

        NumOfFaceletException(std::size_t index);

        ///returns custom message to be printed when exception is invoked
        virtual const char* what() const throw();

};


///Count of each Color
///Check number 2,3 & 4
class NumOfColorException : public Cuception {
    protected:

        ///Index of Color which occurred more or less than 9 times
        std::size_t index;

        ///Number of occurence of this Color at center piece
        std::size_t num_ctr;

        ///Number of occurence of this Color at edge piece
        std::size_t num_edg;

        ///Number of occurence of this Color at corner piece
        std::size_t num_cnr;


    public:

        NumOfColorException(
                std::size_t _index,
                std::size_t _num_ctr,
                std::size_t _num_edg,
                std::size_t _num_cnr
                );

        virtual const char* what() const throw();

};



///To be thrown when Colors on an edge piece are same or opposite i.e.
///when check number 5 fails.
class EdgeColorException : public Cuception {
    private:
        FaceletPosition fp;
        Color c1;
        Color c2;

    public:
        EdgeColorException(FaceletPosition _fp, std::string str);
        virtual const char* what() const throw();
};


///To be thrown when Colors on an corner piece are same or opposite i.e.
///when check number 6 fails.
class CornerColorException : public Cuception {
    private:
        CubeletPosition cp;

    public:
        CornerColorException(CubeletPosition _cp, std::string str);
        virtual const char* what() const throw();
};


#endif
