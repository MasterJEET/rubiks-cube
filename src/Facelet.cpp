/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "Facelet.h"

Facelet::Facelet(): col(C_UNDEFINED){
    //Nothing for now
}

Facelet::Facelet(Color col): col(col){
    //Nothing for now
}

Facelet::Facelet(Position pos): col(C_UNDEFINED), pos(pos){
    //Nothing for now
}

Facelet::Facelet(Color col, Position pos): col(col), pos(pos){
    //Nothing for now
}

Color Facelet::getColor(){
    return col;
}

Position *Facelet::getPosition(){
    return &pos;
}

PositionType *Position::getPositionType(){
    return pos.getType();
}



void Facelet::setColor(Color col){
    this->col = col;
}

void Facelet::setPosition(Position pos){
    this->pos = pos;
}
