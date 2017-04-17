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
        const std::vector<Facelet> vecFac;
        const Position *ppos;
    public:
        Cubelet(Position &pos, Facelet fac1);
        //Cubelet(Position &pos, Facelet fac1, Facelet fac2);
        //Cubelet(Position &pos, Facelet fac1, Facelet fac2, Facelet fac3);
        const std::vector<Facelet> *getFacelet();
        const Position *getPosition();
        void setPosition(Position *ppos);
};

std::ostream& operator<<(std::ostream& os, Cubelet C);

#endif
