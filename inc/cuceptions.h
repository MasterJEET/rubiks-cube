/*! \file   cuceptions.h
 *  \brief  Contains custom exceptions to be used in 'class Cube' (CUbe exCEPTIONS)
 * 
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Jan 2018
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


#endif
