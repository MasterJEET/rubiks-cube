/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Jan 2018
 *
 * */

#include <cuceptions.h>

std::ostringstream NumOfFaceletsException::msg;

NumOfFaceletsException::NumOfFaceletsException(std::size_t _index)
    : runtime_error(":\\ ."), index(_index)
{}

const char* NumOfFaceletsException::what() const throw()
{
    msg.str("");
    msg << "Facelet at Facelet" << Cube::getFaceletPosition(index) << " is not initialized " << runtime_error::what();
    return msg.str().c_str();
}




std::ostringstream NumOfColorsException::msg;

NumOfColorsException::NumOfColorsException(std::size_t _index, std::size_t _count)
    : runtime_error("Each Color can be assigned to exactly 9 Facelets."), index(_index), count(_count)
{}

const char* NumOfColorsException::what() const throw()
{
    msg.str("");
    msg << runtime_error::what() << " " << Cube::getColorFromInt(index) << " occured " << count << " time(s).";
    return msg.str().c_str();
}




std::ostringstream NumOfCenterColorException::msg;

NumOfCenterColorException::NumOfCenterColorException(std::size_t _index, std::size_t _count)
    : runtime_error("Eace Color can be assigned to exactly 1 centerpiece."), index(_index), count(_count)
{}

const char* NumOfCenterColorException::what() const throw()
{
    msg.str("");
    msg << runtime_error::what() << " " << Cube::getColorFromInt(index) << " assigned to " << count << " centerpiece(s).";
    return msg.str().c_str();
}




std::ostringstream SameEdgeColorException::msg;

SameEdgeColorException::SameEdgeColorException(std::vector<FaceSide> _vFS)
    : runtime_error("Edge piece Colors must not be same."), vFS(_vFS)
{}

const char* SameEdgeColorException::what() const throw()
{
    msg.str("");
    msg << "Colors on edge {" << vFS[0] << ", " << vFS[1] << "} are same. " << runtime_error::what();
    return msg.str().c_str();
}




std::ostringstream OppositeEdgeColorException::msg;

OppositeEdgeColorException::OppositeEdgeColorException(std::vector<FaceSide> _vFS)
    : runtime_error("Edge piece Colors must not be opposite."), vFS(_vFS)
{}

const char* OppositeEdgeColorException::what() const throw()
{
    msg.str("");
    msg << "Colors on edge {" << vFS[0] << ", " << vFS[1] << "} are opposite. " << runtime_error::what();
    return msg.str().c_str();
}




std::ostringstream SameCornerColorException::msg;

SameCornerColorException::SameCornerColorException(CubeletPosition _cp)
    : runtime_error("Colors can't be same."), cp(_cp)
{}

const char* SameCornerColorException::what() const throw()
{
    msg.str("");
    msg << "Check Cubelet at " << cp << ". "<< runtime_error::what();
    return msg.str().c_str();
}




std::ostringstream OppositeCornerColorException::msg;

OppositeCornerColorException::OppositeCornerColorException(CubeletPosition _cp)
    : runtime_error("Colors can't be opposite."), cp(_cp)
{}

const char* OppositeCornerColorException::what() const throw()
{
    msg.str("");
    msg << "Check at " << cp << ". "<< runtime_error::what();
    return msg.str().c_str();
}
