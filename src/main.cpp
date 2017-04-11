/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include <iostream>
#include "Position.h"

int main()
{
    Position P = Position(Front, Right, Up);
    std::vector<Face> *vface = P.getFace();
    std::cout << (*vface)[1] << std::endl;
    return 0;
}
