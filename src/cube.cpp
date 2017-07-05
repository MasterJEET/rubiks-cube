/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#include "cube.h"

Cube::Cube(std::istream &is){

    mapFacelet mFacelet;
    //Get all Faces
    for(int i=0; i<6; i++)
        createFace(is, mFacelet);


    //Create Cubelets from mapFacelet and store it in map
    createCubelet(mFacelet);
};

void Cube::createFace(std::istream &is, mapFacelet& mFacelet){

    std::string strFaceSide, strFaceSide2, strColor;
    FaceSide ctrSide, edgeSide, corSide;
    Color col;

    //Get FaceSide and Color for Center Facelet
    is >> strFaceSide >> strColor;
    ctrSide = FaceSideFromLetter(strFaceSide);
    col = ColorFromLetter(strColor);

    //Create Center Facelet and add it to map
    mFacelet[ FaceletPosition(ctrSide) ] = Facelet(col, ctrSide);

    //Get FaceSide and Color for Edge Facelets and add them to map
    for(size_t i=0; i<4; i++){
        is >> strFaceSide >> strColor;
        edgeSide = FaceSideFromLetter(strFaceSide);
        col = ColorFromLetter(strColor);
        FaceletPosition fp(ctrSide, edgeSide);
        mFacelet[ fp ] = Facelet(col, fp);
    }

    //Get FaceSide and Color for Corner Facelets and add them to map
    for(size_t i=0; i<4; i++){
        is >> strFaceSide >> strFaceSide2 >> strColor;
        edgeSide = FaceSideFromLetter(strFaceSide);
        corSide = FaceSideFromLetter(strFaceSide2);
        col = ColorFromLetter(strColor);
        FaceletPosition fp(ctrSide, edgeSide, corSide);
        mFacelet[ fp ] = Facelet(col, fp);
    }


};

void Cube::createCubelet(mapFacelet& mFacelet){
   
    //Vector of all valid FaceSides
    std::vector<FaceSide> vSingleFS = {
        {front} , {back} , {up} , {down} , {right} , {left}
    };

    //Create center Cubelets and add to map
    for( const auto& vfs: vSingleFS ){
        FaceletPosition fp(vfs);
        CubeletPosition cp(vfs);
        mCubelet[ cp ] = Cubelet( mFacelet[fp] );
    }


    //Vector of vector of pair FaceSides
    std::vector< std::vector<FaceSide> > vDoubleFS = { 
                                        { front, up }, { front, right }, { front, down }, { front, left },
                                        { up, right }, { down, right }, { down, left }, { up, left },
                                        { back, up }, { back, right }, { back, down }, { back, left }
                                      };

    for( const auto& vfs: vDoubleFS ){
        FaceletPosition fp1(vfs);
        FaceletPosition fp2(vfs[1], vfs[0]);
        CubeletPosition cp(vfs);
        mCubelet[ cp ] = Cubelet( mFacelet[fp1], mFacelet[fp2] );
    }

    //Vector of vector of triple FaceSides
    std::vector< std::vector<FaceSide> > vTripleFS = { { front, right, up}, { back, right, up }, { back, left, up}, { front, left, up },
                                                       { front, right, down}, { back, right, down }, { back, left, down}, { front, left, down } };

    for( const auto& vfs: vTripleFS ){
        FaceletPosition fp1(vfs);
        FaceletPosition fp2(vfs[1], vfs[0], vfs[2]);
        FaceletPosition fp3(vfs[2], vfs[0], vfs[1]);
        CubeletPosition cp(vfs);
        mCubelet[ cp ] = Cubelet( mFacelet[fp1], mFacelet[fp2], mFacelet[fp3] );
    }
}

