/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Jan 2018
 *
 * */

#include <cuceptions.h>


std::ostringstream Cuception::msg;
std::string Cuception::message;

Cuception::Cuception()
    : runtime_error("")
{}

Cuception::Cuception(std::string str)
    : runtime_error(str)
{}



NumOfFaceletException::NumOfFaceletException(std::size_t _index)
    : Cuception(":\\ ."), index(_index)
{}

const char* NumOfFaceletException::what() const throw()
{
    msg.str("\n");
    msg << "Facelet at Facelet" << Cube::getFaceletPosition(index) << " is not initialized " << runtime_error::what() << std::endl;
    message = msg.str();
    return message.c_str();
}




NumOfColorException::NumOfColorException(
        std::size_t _index,
        std::size_t _num_ctr,
        std::size_t _num_edg,
        std::size_t _num_cnr
):
    Cuception("Each Color can be assigned to exactly 9 Facelets."),
    index(_index), num_ctr(_num_ctr), num_edg(_num_edg), num_cnr(_num_cnr)
{}

const char* NumOfColorException::what() const throw()
{
    message = "\n";
    message = message + runtime_error::what() + " Color " + Color_str[index] + " occured \n" +\
          std::to_string(num_ctr) + " time(s) at center,\n" +
          std::to_string(num_edg) + " time(s) at edge,\n" +
          std::to_string(num_cnr) + " time(s) at corner.\n";
    return message.c_str();
}




SameEdgeColorException::SameEdgeColorException(FaceletPosition _fp)
    : Cuception("Edge piece Colors must not be same."), fp(_fp)
{}

const char* SameEdgeColorException::what() const throw()
{
    msg.str("\n");
    msg << "Color on Facelets at " << CubeletPosition(fp) << " are same: " << runtime_error::what() << std::endl;
    message = msg.str();
    return message.c_str();
}





OppositeEdgeColorException::OppositeEdgeColorException(std::vector<FaceSide> _vFS)
    : Cuception("Edge piece Colors must not be opposite."), vFS(_vFS)
{}

const char* OppositeEdgeColorException::what() const throw()
{
    msg.str("");
    msg << "Colors on edge {" << vFS[0] << ", " << vFS[1] << "} are opposite. " << runtime_error::what();
    return msg.str().c_str();
}





SameCornerColorException::SameCornerColorException(CubeletPosition _cp)
    : Cuception("Colors can't be same."), cp(_cp)
{}

const char* SameCornerColorException::what() const throw()
{
    msg.str("");
    msg << "Check Cubelet at " << cp << ". "<< runtime_error::what();
    return msg.str().c_str();
}





OppositeCornerColorException::OppositeCornerColorException(CubeletPosition _cp)
    : Cuception("Colors can't be opposite."), cp(_cp)
{}

const char* OppositeCornerColorException::what() const throw()
{
    msg.str("");
    msg << "Check at " << cp << ". "<< runtime_error::what();
    return msg.str().c_str();
}
