/*!
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 6th Apr 2019
 *
 * */

#include <cube.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const cube::Side& s){
    return os << cube::side_to_str[static_cast<short>(s)];
}

std::ostream& operator<<(std::ostream& os, const std::vector<cube::Side>& v){
    if(v.empty())
        return os;
    os << cube::side_to_str[static_cast<short>(v[0])];
    for(auto it = v.begin()+1; it != v.end(); it++)
        os << "," << cube::side_to_str[static_cast<short>(*it)];
    return os;
}

std::ostream& operator<<(std::ostream& os, const cube::Color& c){
    return os << cube::color_to_str[static_cast<short>(c)];
}

void cube::Step::normalize()
{
    num = num%4;
    if(num == 3)
        num = -1;
    else if(num == -3)
        num = 1;
}

bool cube::AreOpposite(const Side& s1, const Side& s2)
{
    return opposite[static_cast<short>(s1)] == s2;
}

bool cube::AnyOpposite(const Side& s1, const Side& s2, const Side& s3)
{
    if( AreOpposite(s1,s2) )
        return true;
    if( AreOpposite(s2,s3) )
        return true;
    if( AreOpposite(s1,s3) )
        return true;
    return false;
}

bool cube::AnyEqual(const Side& s1, const Side& s2, const Side& s3)
{
    if(s1 == s2)
        return true;
    if(s2 == s3)
        return true;
    if(s1 == s3)
        return true;
    return false;
}

void cube::Rotate(Side& face, const Side& axis)
{
    if( face == axis || face == opposite[static_cast<short>(axis)] )
        return;

    if(face == Side::Front)
    {
        if(axis == Side::Up){ face = Side::Left; return; }
        else if(axis == Side::Right) { face = Side::Up; return; }
        else
        {
            Rotate(face, opposite[static_cast<short>(axis)]);
            face = opposite[static_cast<short>(face)];
            return;
        }
    }
    else if( face == Side::Up)
    {
        if(axis == Side::Front){ face = Side::Right; return; }
        else if(axis == Side::Right) { face = Side::Back; return; }
        else
        {
            Rotate(face, opposite[static_cast<short>(axis)]);
            face = opposite[static_cast<short>(face)];
            return;
        }
    }
    else if(face == Side::Right)
    {
        if(axis == Side::Front) { face = Side::Down; return; }
        else if(axis == Side::Up) { face = Side::Front; return; }
        else
        {
            Rotate(face, opposite[static_cast<short>(axis)]);
            face = opposite[static_cast<short>(face)];
            return;
        }
    }
    else
    {
        face = opposite[static_cast<short>(face)];
        Rotate(face, axis);
        face = opposite[static_cast<short>(face)];
        return;
    }
}

void cube::Rotate(Side& face, Step& step)
{
    step.normalize();
    if(step.num > 0)
    {
        for(short int i=1; i <= step.num; i++)
            Rotate(face, step.side);
    }
    else if(step.num < 0)
    {
        for(short int i=1; i <= -step.num; i++)
            Rotate(face, opposite[static_cast<short>(step.side)]);
    }
}

cube::Step cube::GetStepFromFront(const Side& target)
{
    Step step;
    if(target == Side::Front)
        step = Step(Side::Front,0);
    else if(target == Side::Back)
        step = Step(Side::Up,2);
    else if(target == Side::Up)
        step = Step(Side::Right);
    else if(target == Side::Down)
        step = Step(Side::Left);
    else if(target == Side::Left)
        step = Step(Side::Up);
    else if(target == Side::Right)
        step = Step(Side::Down);
    return step;
}

short cube::FletPosIndex(std::vector<Side> v)
{
    if(v.empty() || v.size()>3)
        return -1;
    Step step = GetStepFromFront(v[0]);
    step.inverse();

    // Unique number associated with each side
    unsigned short num_side = static_cast<unsigned short>(v[0]);
    unsigned short num_flet;
    Rotate(v[1],step);
    Rotate(v[2],step);

    if(v.size() == 1)
        num_flet = 0;
    else if(v.size() == 2)
    {
        switch(v[1])
        {
            case Side::Up:
                num_flet = 1;
                break;
            case Side::Right:
                num_flet = 2;
                break;
            case Side::Down:
                num_flet = 3;
                break;
            case Side::Left:
                num_flet = 4;
                break;
            default:
                break;
        }
    }
    else if(v.size() == 3)
    {
        if(v[1]>v[2])
            std::swap(v[1],v[2]);
        if(v[1] == Side::Up && v[2] == Side::Right)
            num_flet = 5;
        if(v[1] == Side::Down && v[2] == Side::Right)
            num_flet = 6;
        if(v[1] == Side::Down && v[2] == Side::Left)
            num_flet = 7;
        if(v[1] == Side::Up && v[2] == Side::Left)
            num_flet = 8;
    }

    return num_side*CUBE_SIZE*CUBE_SIZE + num_flet;
}

short cube::FletPosIndex(const Side& s1)
{
    return FletPosIndex({s1});
}
short cube::FletPosIndex(const Side& s1, const Side& s2)
{
    return FletPosIndex({s1,s2});
}
short cube::FletPosIndex(const Side& s1, const Side& s2, const Side& s3)
{
    return FletPosIndex({s1,s2,s3});
}

char cube::Cube::next_(std::istream& is)
{
    std::string word;
    is >> word;
    return word[0];
}

void cube::Cube::parse_linear_input_(std::istream& is)
{
    for(short int i=0; i<6;i++)
        face_from_linear_(is);

    std::cout << "Successfully parsed." << std::endl;
}

void cube::Cube::face_from_linear_(std::istream& is)
{
    char c = next_(is);
    Side f = char_to_side.at(c);
    Step s = GetStepFromFront(f);

    auto fls(front_linear_sequence);
    for(auto& v: fls)
        cube::Rotate(v,s);

    Color col;
    for(auto& v: fls)
    {
        c = next_(is);
        col = char_to_color.at(c);
        colors_[ FletPosIndex(v) ] = col;
    }
}

void cube::Cube::rotate_(std::vector<Side> v, Step s)
{
    s.normalize();
    s.inverse();
    auto n(v);
    cube::Rotate(n,s);

    if(s.num == 1 || s.num == -1)
    {
        swap_(v,n);

        cube::Rotate(v,s);
        cube::Rotate(n,s);
        swap_(v,n);

        cube::Rotate(v,s);
        cube::Rotate(n,s);
        swap_(v,n);
    }
    else if(s.num == 2)
    {
        swap_(v,n);

        cube::Rotate(v,s.side);
        cube::Rotate(n,s.side);
        swap_(v,n);
    }
}

void cube::Cube::Rotate(Step& step)
{
    Side f = step.side;
    Side u = Side::Up;
    Side r = Side::Right;

    Step s = GetStepFromFront(f);
    cube::Rotate(u,s);
    cube::Rotate(r,s);

    rotate_(std::vector<Side>({f,u}), step);
    rotate_(std::vector<Side>({u,f}), step);
    rotate_(std::vector<Side>({f,u,r}), step);
    rotate_(std::vector<Side>({u,f,r}), step);
    rotate_(std::vector<Side>({r,f,u}), step);
}
