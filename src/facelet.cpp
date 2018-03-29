/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "facelet.h"

FaceletPosition relative(const FaceletPosition& P1, const FaceletPosition& P2)
{ return P1.relative(P2.first() ); }

Facelet& Facelet::operator*=(const FaceSide& rhs){
    pos *= rhs;
    return *this;
}


std::string Facelet::colorFormat(){
    std::string setcolor, reset;
    reset = "\033[0m";

    switch(col){
        case White:
            setcolor = "\033[37m";
            break;
        case Orange:
            setcolor = "\e[38;5;202m";
            break;
        case Red:
            setcolor = "\033[31m";
            break;
        case Yellow:
            setcolor = "\e[93m";
            break;
        case Green:
            setcolor = "\033[32m";
            break;
        case Blue:
            setcolor = "\033[34m";
            break;
        default:
            break;
    }

    return setcolor + FaceSide_str[side()][0] + reset;

}

