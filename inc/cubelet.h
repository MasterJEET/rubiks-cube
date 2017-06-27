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

class Cubelet{
    private:

        //Holds Facelets for a given cubelet
        std::vector<Facelet*> vecFac;

        //Holds Position of a given cubelet
        Position pos;

    public:

        //Default constructor
        Cubelet(){};
        
        //Constructor for Center cubelets
        Cubelet(Facelet* p_fac1);
        
        //Constructor for Edge cubelets
        Cubelet(Facelet* p_fac1, Facelet* p_fac2);
        
        //Constructor for Corner cubelets
        Cubelet(Facelet* p_fac1, Facelet* p_fac2, Facelet* p_fac3);
       
        //Returns vector of facelets for the cubelet
        const std::vector<Facelet*> *getFacelet() const {return &vecFac;}
       
        // Returns vecFac[index]
        Facelet getFaceletAt(size_t index) const{ return *vecFac.at(index);}

        //Returns Position
        Position getPosition() const{ return pos;}

        //Sets Position for cubelet
        void setPosition(const Position _pos){ pos = _pos; }

        //operator<< overloading for writing Cubelet to ostream
        friend std::ostream& operator<<(std::ostream& os, Cubelet C);

        //Equality
        friend bool operator==(const Cubelet& lhs, const Cubelet& rhs);

        //Inequality
        friend bool operator!=(const Cubelet& lhs, const Cubelet& rhs);
};


#endif
