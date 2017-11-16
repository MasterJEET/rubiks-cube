/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#include "cube.h"

Cube::Cube(std::istream &is){

    hashFacelet hFacelet;
    ///Get all Faces
    for(int i=0; i<6; i++)
        createFace(is, hFacelet);


    ///Create Cubelets from hashFacelet and store it in map
    createCubelet(hFacelet);
};

void Cube::createFace(std::istream &is, hashFacelet& hFacelet){

    std::string strFaceSide, strFaceSide2, strColor;
    FaceSide ctrSide, edgeSide, corSide;
    Color col;

    ///Get FaceSide and Color for Center Facelet
    is >> strFaceSide >> strColor;
    ctrSide = FaceSideFromLetter(strFaceSide);
    col = ColorFromLetter(strColor);

    ///Create Center Facelet and add it to map
    hFacelet[ FaceletPosition(ctrSide) ] = Facelet(col, ctrSide);

    ///Get FaceSide and Color for Edge Facelets and add them to map
    for(size_t i=0; i<4; i++){
        is >> strFaceSide >> strColor;
        edgeSide = FaceSideFromLetter(strFaceSide);
        col = ColorFromLetter(strColor);
        FaceletPosition fp(ctrSide, edgeSide);
        hFacelet[ fp ] = Facelet(col, fp);
    }

    ///Get FaceSide and Color for Corner Facelets and add them to map
    for(size_t i=0; i<4; i++){
        is >> strFaceSide >> strFaceSide2 >> strColor;
        edgeSide = FaceSideFromLetter(strFaceSide);
        corSide = FaceSideFromLetter(strFaceSide2);
        col = ColorFromLetter(strColor);
        FaceletPosition fp(ctrSide, edgeSide, corSide);
        hFacelet[ fp ] = Facelet(col, fp);
    }


};

void Cube::createCubelet(hashFacelet& hFacelet){
   
    ///Vector of all valid FaceSides
    std::vector<FaceSide> vSingleFS = {
        {front} , {back} , {up} , {down} , {right} , {left}
    };

    ///Create center Cubelets and add to map
    for( const auto& vfs: vSingleFS ){
        FaceletPosition fp(vfs);
        CubeletPosition cp(vfs);
        hCubelet[ cp ] = Cubelet( hFacelet[fp] );
    }


    ///Vector of vector of pair FaceSides
    std::vector< std::vector<FaceSide> > vDoubleFS = { 
                                        { front, up }, { front, right }, { front, down }, { front, left },
                                        { up, right }, { down, right }, { down, left }, { up, left },
                                        { back, up }, { back, right }, { back, down }, { back, left }
                                      };

    for( const auto& vfs: vDoubleFS ){
        FaceletPosition fp1(vfs);
        FaceletPosition fp2(vfs[1], vfs[0]);
        CubeletPosition cp(vfs);
        hCubelet[ cp ] = Cubelet( hFacelet[fp1], hFacelet[fp2] );
    }

    ///Vector of vector of triple FaceSides
    std::vector< std::vector<FaceSide> > vTripleFS = { { front, right, up}, { back, right, up }, { back, left, up}, { front, left, up },
                                                       { front, right, down}, { back, right, down }, { back, left, down}, { front, left, down } };

    for( const auto& vfs: vTripleFS ){
        FaceletPosition fp1(vfs);
        FaceletPosition fp2(vfs[1], vfs[0], vfs[2]);
        FaceletPosition fp3(vfs[2], vfs[0], vfs[1]);
        CubeletPosition cp(vfs);
        hCubelet[ cp ] = Cubelet( hFacelet[fp1], hFacelet[fp2], hFacelet[fp3] );
    }
}

void Cube::show(const FaceSide f){
    auto tlist = getFaceletPosition(f);
    auto it = tlist.begin();
    while( it != tlist.end()){
        for(int i=0;i<3;i++,it++){
            Color c = getFacelet(*it).getColor();
            std::cout << colorFormat(c) << " " ;
        }
        std::cout << std::endl;
    }
}



/*! Fetch list of FaceletPositions associated with a given FaceSide
 *
 *                U U U
 *                U U U
 *                U U U
 *          B B B L L L F F F R R R      1 2 3 #
 *          B B B L L L F F F R R R      4 5 6 # This is the sequence
 *          B B B L L L F F F R R R      7 8 9 #
 *                D D D
 *                D D D
 *                D D D
 * Returns above positions for a face,
 * Order of positions in the list is depicted by above diagram
 *
 * */

std::list<FaceletPosition> Cube::getFaceletPosition(const FaceSide f){
    std::list<FaceletPosition> tlist;
    FaceSide u,r,d,l;

    switch(f){
        case Front:
            u = up; r = right; d = down; l = left;
            break;
        case Back:
            u = up; r = left; d = down; l = right;
            break;
        case Right:
            u = up; r = back; d = down; l = front;
            break;
        case Left:
            u = up; r = front; d = down; l = back;
            break;
        case Up:
            u = back; r = right; d = front; l = left;
            break;
        case Down:
            u = front; r = right; d = back; l = left;
            break;
        default:
            break;
    }

    tlist.push_back({ f,l,u }); tlist.push_back({ f,u });   tlist.push_back({ f,r,u });
    tlist.push_back({ f,l });   tlist.push_back(f);         tlist.push_back({ f,r });
    tlist.push_back({ f,l,d }); tlist.push_back({ f,d });   tlist.push_back({ f,r,d });

    return tlist;
}
