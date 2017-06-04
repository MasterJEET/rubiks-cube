/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 17th Apr 2017
 *
 * */

#ifndef CUBELET_H
#define CUBELET_H

#include "Facelet.h"
#include "Position.h"
#include <vector>

class Cubelet{
    private:

        //Holds Facelets for a given cubelet
        const std::vector<Facelet *> vecFac;

        //Holds Position of a given cubelet
        const Position *ppos;

    public:
        
        //Constructor for Center cubelets
        //Cubelet(const Position * const ppos, Facelet * const fac1);
        Cubelet(Facelet * const fac1);
        
        //Constructor for Edge cubelets
        Cubelet(const Position * const ppos, Facelet * const fac1, Facelet * const fac2);
        
        //Constructor for Corner cubelets
        Cubelet(const Position * const ppos, Facelet * const fac1, Facelet * const fac2, Facelet * const fac3);
       
        //Returns vector of facelets for the cubelet
        const std::vector<Facelet *> * const getFacelet();
       
        // Returns vecFac[index]
        Facelet *getFaceletAt(size_t index) const;

        //Returns pointer to Position
        const Position * getPosition() const;

        //Sets Position for cubelet
        void setPosition(const Position * const ppos);
};

std::ostream& operator<<(std::ostream& os, Cubelet C);

#endif
