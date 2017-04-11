/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */
#if __STDC_VERSION__ < 199901L
# if __GNUC__ >= 2
#  define __func__ __FUNCTION__
# else
#  define __func__ "<unknown>"
# endif
#endif

#include <vector>
#include <stdexcept>

enum Face { Front, Back, Up, Down, Left, Right, F_UNDEFINED=-1 };
enum PositionType { Center, Edge, Corner };

class Position {
    private:
        std::vector<Face> vecFace;
        PositionType ptype;
        bool areOpposite(Face first, Face second);                                  //Check if given pair of Faces are opposite of each other
        bool anyOpposite(Face first, Face second, Face third);                      //Check if any of the given Faces form opposite Faces
    public:
        Position();
        Position(PositionType ptype);
        Position(Face first);
        Position(Face first, Face second);
        Position(Face first, Face second, Face third);                              //For initializng all three Faces from parameter list
        std::vector<Face> *getFace();
        PositionType *getType();
        void setFace(std::size_t pos, Face face);
        void setFace(Face first);
        void setFace(Face first, Face second);
        void setFace(Face first, Face second, Face third);
        void setType(PositionType ptype);
};
