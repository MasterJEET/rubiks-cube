/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 17th Apr 2017
 *
 * */

#ifndef CUBELET_H
#define CUBELET_H

#include "facelet.h"
#include "position.h"
#include <unordered_map>
#include <vector>

typedef std::unordered_map<FaceletPosition, Facelet> hashFacelet;


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


        ///Equality
        friend bool operator==(const CubeletPosition& lhs, const CubeletPosition& rhs);

        ///Inequality
        friend bool operator!=(const CubeletPosition& lhs, const CubeletPosition& rhs){ return !(lhs == rhs); }
};


class Cubelet{
    private:

        ///to hold Facelets with FaceletPosition as the key
        hashFacelet hFacelet;
        ///Holds Position of Cubelet in the Cube
        CubeletPosition pos;

    public:

        ///Default constructor
        Cubelet(){};
        
        ///Constructor for Center cubelets
        Cubelet(Facelet fac1);
        
        ///Constructor for Edge cubelets
        Cubelet(Facelet fac1, Facelet fac2);
        
        ///Constructor for Corner cubelets
        Cubelet(Facelet fac1, Facelet fac2, Facelet fac3);

        ///Initializaton from vector of Facelets
        Cubelet( std::vector<Facelet> _vecFac );
       
        ///Returns vector of facelets for the cubelet
        const hashFacelet getMapFacelet() const {return hFacelet;}
       
        /// Returns vecFac[index]
        Facelet getFacelet(const FaceletPosition& fp) const{ return hFacelet.at(fp);}

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
};



namespace std {
    template <>
        struct hash<CubeletPosition> {
            typedef CubeletPosition argument_type;
            typedef std::size_t result_type;
            
            result_type operator()(const argument_type& p) const{
                FaceSide f1 = p.getSideAt(0);
                FaceSide f2 = p.getSideAt(1);
                FaceSide f3 = p.getSideAt(2);

                /// Arrange in decreasing order
                /// This is required to make this implementaion
                /// insensitive to order of FaceSides in Position object i.e.
                /// (front, up, left) == (up, left, front) == (left, up, front)

                if(f1 > f2)
                    swap(f1, f2);
                if(f2 > f3)
                    swap(f2, f3);
                if(f1 > f2)
                    swap(f1, f2);

                result_type i1 = std::hash<int>()(static_cast<result_type>(f1));
                result_type i2 = std::hash<int>()(static_cast<result_type>(f2));
                result_type i3 = std::hash<int>()(static_cast<result_type>(f3));

                return ( i1*100 + i2*10 + i3 );
            }
        };
}


#endif
