/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 17th Apr 2017
 *
 * */

#ifndef CUBELET_H
#define CUBELET_H

//Maximum number of facelets in 3x3 cube
#define __MAX_FAC__   54

#include "facelet.h"
#include "position.h"
#include <unordered_map>
#include <vector>
#include <array>
#include <list>

typedef std::array<Facelet, __MAX_FAC__> arrFacelet;
typedef std::list<Facelet> listFacelet;
typedef std::list<FaceletPosition> listFaceletPosition;


class CubeletPosition : public Position {
    public:
        ///Constructors same as those of Position
        CubeletPosition(){};
        CubeletPosition(const FaceSide first): Position(first){};
        CubeletPosition(const FaceSide first, const FaceSide second): Position(first, second){};
        CubeletPosition(const FaceSide first, const FaceSide second, const FaceSide third): Position(first, second, third){};
        CubeletPosition(const std::vector<FaceSide> _vecSide): Position(_vecSide){};
        
        ///New construtor, initialize from  FaceletPosition
        CubeletPosition(const FaceletPosition fp): Position( *fp.getSide() ){};

        ///operator<< overloading to write CubeletPosition to ostream
        friend std::ostream& operator<<(std::ostream& os, CubeletPosition P);

        ///Equality
        friend bool operator==(const CubeletPosition& lhs, const CubeletPosition& rhs);

        ///Inequality
        friend bool operator!=(const CubeletPosition& lhs, const CubeletPosition& rhs){ return !(lhs == rhs); }

        ///Type operator, converting to size_t to be used as array index later
        operator std::size_t() const;
};


class Cubelet{

    private:

        ///to hold Facelets in array with FaceletPosition as index
        static arrFacelet aFacelet;
        ///Holds Position of Cubelet in the Cube
        CubeletPosition pos;

    public:

        Cubelet(){};
        
        ///Constructor for Center cubelets
        Cubelet(Facelet fac1);
        
        ///Constructor for Edge cubelets
        Cubelet(Facelet fac1, Facelet fac2);
        
        ///Constructor for Corner cubelets
        Cubelet(Facelet fac1, Facelet fac2, Facelet fac3);

        ///Initializaton from vector of Facelets
        Cubelet( std::vector<Facelet> _vecFac );
       
        ///Return list of FaceletPostions associated with this Cubelet
        listFaceletPosition getFaceletPositionList() const;

        ///Fetch a list of Facelets in this Cubelet
        listFacelet getFaceletList() const;

        ///Returns Facelet at given FaceletPositon 
        Facelet getFacelet(const FaceletPosition& fp) const{ return aFacelet.at(fp);}

        ///Returns Position
        CubeletPosition getPosition() const{ return pos;}

        ///Sets Position for cubelet
        void setPosition(const CubeletPosition _pos){ pos = _pos; }

        ///operator<< overloading for writing Cubelet to ostream
        friend std::ostream& operator<<(std::ostream& os, Cubelet C);

        ///Equality
        friend bool operator==(const Cubelet& lhs, const Cubelet& rhs);

        ///Inequality
        friend bool operator!=(const Cubelet& lhs, const Cubelet& rhs){ return !(lhs == rhs); }

        /// Rotate about axis defined by FaceSide, change the object
        Cubelet& operator*=(const FaceSide& rhs);

        /// Rotate about axis defined by FaceSide, return the object
        friend Cubelet operator*(Cubelet lhs, const FaceSide& rhs){ lhs *= rhs; return lhs; }
        
        friend class Cube;

};


#endif
