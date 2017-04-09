/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

enum Face { Front, Back, Up, Down, Left, Right };
enum PositionType { Center, Edge, Corner };

class Position {
    private:
        Face *arrFace;
        PositionType ptype;
    public:
        Position();
        Position(PositionType ptype);
        Position(Face first);
        Position(Face first, Face second);
        Position(Face first, Face second, Face third);
        Face **getFace();
        PositionType *getType();
};
