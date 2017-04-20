/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include <iostream>
#include <fstream>
#include "Face.h"
#include "common.h"

//Just for few testing

int main(int argc, char **argv)
{
    signal(SIGABRT, handler);
    std::ifstream in("/home/masterjeet/rubiks-cube/dat/front.dat");
    Face F = Face(in);
    F.printAllFacelet();
    return 0;
}
