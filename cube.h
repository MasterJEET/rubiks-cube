/*! \file   cube.h
 *  \brief  Can serve as API for cube solving algorithms
 * 
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 6th Apr 2019
 *
 * */

#ifndef CUBE_H
#define CUBE_H

#include <memory>   // unique_ptr, shared_ptr
#include <array>
#include <string>
#include <vector>
#include <istream>
#include <unordered_map>

namespace cube {
    enum class Color: short;
    enum class Side: short;
}

std::ostream& operator<<(std::ostream& os, const cube::Side& s);
std::ostream& operator<<(std::ostream& os, const std::vector<cube::Side>& v);
std::ostream& operator<<(std::ostream& os, const cube::Color& c);

namespace cube {
const unsigned short int CUBE_SIZE = 3;

enum class Color: short {
    White = 0,
    Yellow,
    Orange,
    Red,
    Green,
    Blue
};

enum class Side: short {
    Front=0,
    Back,
    Up,
    Down,
    Left,
    Right
};

struct Step {
    Side side;

    /// Number of 90 degree rotations about side
    /// Positive for clockwise, negative anti-clockwise
    short int num;

    Step(){}
    Step(const Side& _side, const short int& _num = 1):
        side(_side),
        num(_num)
    { normalize(); }
    Step(const short int& _num, const Side& _side): Step(_side, _num){}

    void inverse(){ num = -num; }
    void normalize();
};

const static std::unordered_map<char,Color> char_to_color = {
    {'W',Color::White},    {'Y',Color::Yellow},   {'O',Color::Orange},
    {'R',Color::Red},      {'B',Color::Blue},     {'G',Color::Green}
};

const static std::unordered_map<char,Side> char_to_side = {
    {'F',Side::Front},    {'B',Side::Back},     {'U',Side::Up},
    {'D',Side::Down},     {'L',Side::Left},     {'R',Side::Right}
};

const static std::array<std::string,6> side_to_str = {
    "Front","Back","Up","Down","Left","Right"
};

const static std::array<std::string,6> color_to_str = {
    "White","Yellow","Orange","Red","Green","Blue"
};

/// Order of entries is very very important here,
/// linear format parsing is dependent on this
//Ensure that vector can't be modified here
const static std::array<std::vector<Side>,CUBE_SIZE*CUBE_SIZE> front_linear_sequence = {
    std::vector<Side>({Side::Front,Side::Up,Side::Left}),     std::vector<Side>({Side::Front,Side::Up}),      std::vector<Side>({Side::Front,Side::Up,Side::Right}),
    std::vector<Side>({Side::Front,Side::Left}),        std::vector<Side>({Side::Front}),         std::vector<Side>({Side::Front,Side::Right}),
    std::vector<Side>({Side::Front,Side::Down,Side::Left}),   std::vector<Side>({Side::Front,Side::Down}),    std::vector<Side>({Side::Front,Side::Down,Side::Right})
};

const static std::array<Side,6> opposite = {
    Side::Back, Side::Front, Side::Down, Side::Up, Side::Right, Side::Left
};

bool AreOpposite(const Side& s1, const Side& s2);
bool AnyOpposite(const Side& s1, const Side& s2, const Side& s3);
bool AnyEqual(const Side& s1, const Side& s2, const Side& s3);


/*! Rotates side about axis
 *
 * Similar to cartesian vector multiplication
 * Need more description here
 * */
void Rotate(Side& face, const Side& axis);
void Rotate(Side& face, Step& step);

// A can only be Side or Step
template<typename A>
void Rotate(std::vector<Side>& side_vec, A& axis)
{
    for(auto& side: side_vec)
        Rotate(side, axis);
}

/*! Returns 'standard step' required for the Front face
 * to become 'target'
 *
 * 'Standard step' need more elaboration. There can be multiple steps
 * but we return only a particular sequence
 * */
Step GetStepFromFront(const Side& target);

/*! Returns int mapped with a Facelet position
 *
 * Explain Facelet position
 * */
short FletPosIndex(std::vector<Side> v);
short FletPosIndex(const Side& s1);
short FletPosIndex(const Side& s1, const Side& s2);
short FletPosIndex(const Side& s1, const Side& s2, const Side& s3);

class Cube {
private:
    std::array<Color,CUBE_SIZE*CUBE_SIZE*6> colors_;

    char next_(std::istream& is);

    /*! Assumes input are in linear format
     *
     * Explain linear format
     * */ 
    void parse_linear_input_(std::istream& is);
    void face_from_linear_(std::istream& is);

    void swap_(std::vector<Side>& v, std::vector<Side>& n){
        std::swap( colors_[FletPosIndex(v)], colors_[FletPosIndex(n)] );
    }
    // Rotates particular set of Facelets
    void rotate_(std::vector<Side> v, Step s);

public:
    Cube(std::istream& is){ parse_linear_input_(is); }

    /// Rotate the face specified in step.side as per step
    void Rotate(Step& step);
};

}   // namespace cube

#endif  //  CUBE_H
