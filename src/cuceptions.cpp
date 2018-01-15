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
