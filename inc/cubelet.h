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
#include <vector>

class CubeletPosition : public Position {
    public:
        //Constructors same as those of Position
        CubeletPosition(){};
        CubeletPosition(const FaceSide first): Position(first){};
        CubeletPosition(const FaceSide first, const FaceSide second): Position(first, second){};
        CubeletPosition(const FaceSide first, const FaceSide second, const FaceSide third): Position(first, second, third){};
        CubeletPosition(const std::vector<FaceSide> _vecSide): Position(_vecSide){};
        
        //New construtor, initialize from  FaceletPosition
        CubeletPosition(const FaceletPosition fp): Position( *fp.getSide() ){};


        //Equality
        friend bool operator==(const CubeletPosition& lhs, const CubeletPosition& rhs);

        //Inequality
        friend bool operator!=(const CubeletPosition& lhs, const CubeletPosition& rhs){ return !(lhs == rhs); }
};


class Cubelet{
    friend class Cube;
    private:

        //Holds Facelets for a given cubelet
        std::vector<Facelet*> vecFac;
        //Holds FaceletPositions which refers to Facelets
        std::vector<FaceletPosition> vecFP;
        //Holds Position of a given cubelet
        CubeletPosition pos;

    public:

        //Default constructor
        Cubelet(){};
        
        //Constructor for Center cubelets
        Cubelet(Facelet* p_fac1);
        
        //Constructor for Edge cubelets
        Cubelet(Facelet* p_fac1, Facelet* p_fac2);
        
        //Constructor for Corner cubelets
        Cubelet(Facelet* p_fac1, Facelet* p_fac2, Facelet* p_fac3);
       
        //Constructor for Center cubelets
        Cubelet(FaceletPosition cp1);
        
        //Constructor for Edge cubelets
        Cubelet(FaceletPosition cp1, FaceletPosition cp2);
        
        //Constructor for Corner cubelets
        Cubelet(FaceletPosition cp1, FaceletPosition cp2, FaceletPosition cp3);

        //Returns vector of facelets for the cubelet
        const std::vector<Facelet*> *getFacelet() const {return &vecFac;}
       
        // Returns vecFac[index]
        Facelet getFaceletAt(size_t index) const{ return *vecFac.at(index);}

        //Returns Position
        Position getPosition() const{ return pos;}

        //Sets Position for cubelet
        void setPosition(const CubeletPosition _pos){ pos = _pos; }

        //operator<< overloading for writing Cubelet to ostream
        friend std::ostream& operator<<(std::ostream& os, Cubelet C);

        //Equality
        friend bool operator==(const Cubelet& lhs, const Cubelet& rhs);

        //Inequality
        friend bool operator!=(const Cubelet& lhs, const Cubelet& rhs){ return !(lhs == rhs); }
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

                // Arrange in decreasing order
                // This is required to make this implementaion
                // insensitive to order of FaceSides in Position object i.e.
                // (front, up, left) == (up, left, front) == (left, up, front)

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
