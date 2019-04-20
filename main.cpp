#include <cube.h>

#include <iostream>
//#include <chrono>
//#include <thread>


using namespace cube;
int main()
{
    //std::this_thread::sleep_for(std::chrono::seconds(30));
    //Facelet f1(Front,Red), f2(Left,Blue), f3(Up,White);
    //Cubelet C1(f1,f2,f3);
    //std::cout << "face: " << side_to_str[C1.facelets[0]->side] << std::endl;

    Cube C(std::cin);
    //C.Rotate(Front, Right);
    //C.Rotate(Front, Step(Left,2));
    return 0;
}
