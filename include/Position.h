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

enum FaceSide { Front, Back, Up, Down, Left, Right, F_UNDEFINED = -1 };
enum PositionType { Center, Edge, Corner, P_UNDEFINED = -1 };

class Position {
    private:
        std::vector<FaceSide> vecSide;                                              //Holds FaceSides
        PositionType ptype;                                                         //Holds PositionType
        bool areOpposite(FaceSide first, FaceSide second);                          //Check if given pair of FaceSides are opposite of each other
        bool anyOpposite(FaceSide first, FaceSide second, FaceSide third);          //Check if any of the given FaceSides form opposite FaceSides
    public:
        Position();                                                                 //Default constructor
        //Position(PositionType ptype);                                             //For initializing PsoitionType
        Position(FaceSide first);                                                   //For initailizing a FaceSide from parameter, specifies which center
        Position(FaceSide first, FaceSide second);                                  //For initializing two FaceSides from parameter list, specifies which edge
        Position(FaceSide first, FaceSide second, FaceSide third);                  //For initializing all three FaceSides from parameter list, specifies which corner
        std::vector<FaceSide> *getSide();                                           //Returns pointer to 'vecSide'
        FaceSide getFirstSide();                                                    //Returns first FaceSide of vecSide i.e. vecSide[0]
        PositionType *getType();                                                    //Returns pointer to 'ptype'
        //void setSide(std::size_t pos, FaceSide face);                             //Unimplemented as not required
        void setSide(FaceSide first);                                               //Sets FaceSide, which Center
        void setSide(FaceSide first, FaceSide second);                              //Sets two FaceSides, which Edge
        void setSide(FaceSide first, FaceSide second, FaceSide third);              //Sets all FaceSides, which Corner
        //void setType(PositionType ptype);                                         //Sets PositionType, Unimplemented
};
