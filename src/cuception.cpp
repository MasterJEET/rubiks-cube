/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Jan 2018
 *
 * */

#include <cuception.h>


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
    std::ostringstream oss;
    oss << "\nFacelet at Facelet" << Cube::getFaceletPosition(index) << " is not initialized " << runtime_error::what() << std::endl;
    message = oss.str();
    return message.c_str();
}




NumOfColorException::NumOfColorException(
        std::size_t _index,
        std::size_t _num_ctr,
        std::size_t _num_edg,
        std::size_t _num_cnr
):
    Cuception("Each Color can be assigned to exactly 4 corner, 4 edge and 1 center Facelets."),
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




EdgeColorException::EdgeColorException(FaceletPosition _fp, std::string str)
    : Cuception(str), fp(_fp)
{}

const char* EdgeColorException::what() const throw()
{
    std::ostringstream oss;
    oss << "\nCheck Colors on edge Cubelet at " << CubeletPosition(fp) << ".\n" << runtime_error::what() << std::endl;
    message = oss.str();
    return message.c_str();
}





CornerColorException::CornerColorException(CubeletPosition _cp, std::string str)
    : Cuception(str), cp(_cp)
{}

const char* CornerColorException::what() const throw()
{
    std::ostringstream oss;
    oss << "\nCheck Colors on corner Cubelet at " << cp << ".\n"<< runtime_error::what() << std::endl;
    message = oss.str();
    return message.c_str();
}
