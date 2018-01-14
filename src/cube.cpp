/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#include "cube.h"
#include "cuceptions.h"
#include <iterator>

vecCletPos Cube::vCletPos (__NUM_CUBELET__);
vecFletPos Cube::vFletPos (__NUM_FACELET__);
std::vector<Color> Cube::vCol (__NUM_FACE__);
std::size_t Cube::num_of_instances = 0;

Cube::Cube(){

    num_of_instances ++;

    if(num_of_instances == 1){
        mapIntToCubeletPosition();
        mapIntToFaceletPosition();
        mapIntToColor();
    }

}

Cube::Cube(std::istream &is): Cube(){

    vecFacelet vFacelet(__NUM_FACELET__);                                       //Array for storing Facelets with FaceletPosition as key
    arrNumber aNumOfCol{0,0,0,0,0,0};                                           //Keep tack of number of each valid (not undefside) Colors encountered
    arrBool aIsSet{false,false,false,false,false,false};                        //Use to check if any Center Facelets with given Color has been set
    arrColor aOppColor{undefcol,undefcol,undefcol,undefcol,undefcol,undefcol};  //Contain opposite Color

    //Get all Faces
    for(int i=0; i<6; i++)
        createFaceFromLinearInput(is, vFacelet, aNumOfCol, aIsSet);

    //Check if all required Facelets are created
    vecFacelet::const_iterator iter = std::find( std::begin(vFacelet), std::end(vFacelet), Facelet() );
    if( iter != std::end(vFacelet) )
        throw NumOfFaceletsException(  iter - vFacelet.begin() );

    //Number of All six Colors must be exactly 9
    for(std::size_t i=0; i < aNumOfCol.size(); i++ )
    {
        std::size_t count = aNumOfCol[i];
        if(count != 9){
            throw NumOfColorsException(i, count);
        }
    }

    //Check Colors on Center pieces are unique
    bool are_ctr_col_unique = std::find(std::begin(aIsSet), std::end(aIsSet), false)  == std::end(aIsSet);
    if(!are_ctr_col_unique)
        throw std::runtime_error("Color on each Center Facelet (= Cubelet) must be unique.");

    //Finding opposite of each Color
    setOppColor(vFacelet, aOppColor);

    ///Check that No edge Cubelet have
    ///     1. same Color on more than one of its Facelets
    ///     2. Facelets with opposite Color (Color of Centerpiece located on opposite FaceSide)
    for(const auto& vfs: getEdgeFaceSide())
    {
        FaceletPosition fp1(vfs);
        FaceletPosition fp2( vfs[1], vfs[0] );
        Facelet f1( vFacelet[fp1] );
        Facelet f2( vFacelet[fp2] );

        bool are_same = f1.getColor() == f2.getColor();
        if(are_same)
            throw std::runtime_error("Colors on two Facelets of same Cubelet are same.");

        //bool are_opp = aOppColor[ f1.getColor() ] == f2.getColor();
    }

    //Create Cubelets from vecFacelet and store it in Cubelet array
    createCube(vFacelet);
};


void Cube::mapIntToCubeletPosition(){

    //Create mappings of NUMBER -> CUBELET POSITION
    FaceSide f = front;
    FaceSide b = opposite(f);
    for(const auto cp: vecEdgeEquivalence<CubeletPosition>(f) )     vCletPos[ cp ] = cp;
    for(const auto cp: vecCornerEquivalence<CubeletPosition>(f) )   vCletPos[ cp ] = cp;
    for(const auto cp: vecMidEdgeEquivalence<CubeletPosition>(f) )  vCletPos[ cp ] = cp;
    for(const auto cp: vecCenterEquivalence<CubeletPosition>(f) )   vCletPos[ cp ] = cp;
    for(const auto cp: vecEdgeEquivalence<CubeletPosition>(b) )     vCletPos[ cp ] = cp;
    for(const auto cp: vecCornerEquivalence<CubeletPosition>(b) )   vCletPos[ cp ] = cp;
    vCletPos[ CubeletPosition(f) ] = CubeletPosition(f);
    vCletPos[ CubeletPosition(b) ] = CubeletPosition(b);

}

void Cube::mapIntToFaceletPosition(){
    FaceSide f = front;
    FaceSide b = opposite(f);
    FaceSide u,r,d,l;
    setEquivalentFaceSide(f,u,r,d,l);

    for(const auto fs: {f,b,u,r,d,l}){
        for(const auto fp: getEquivalentFletPos(fs)) vFletPos[ fp ] = fp;
    }
}


void Cube::mapIntToColor(){
    vCol[white]     = white;
    vCol[red]       = red;
    vCol[yellow]    = yellow;
    vCol[orange]    = orange;
    vCol[green]     = green;
    vCol[blue]      = blue;
}


void Cube::createFaceFromStepInput(std::istream &is, vecFacelet& vFacelet, arrNumber& aNumOfCol, arrBool& aIsSet){

    FaceSide ctrSide, edgeSide, corSide;
    Color col;

    //Get FaceSide and Color for Center Facelet
    assertFaceSide(is, ctrSide );
    assertColor(is, col );

    aNumOfCol[col] ++;
    aIsSet[col] = true;

    //Create Center Facelet and add it to array
    vFacelet[ FaceletPosition(ctrSide) ] = Facelet(col, ctrSide);

    //Get FaceSide and Color for Edge Facelets and add them to array
    for(size_t i=0; i<4; i++){
        assertFaceSide(is, edgeSide );
        assertColor(is, col);
        aNumOfCol[col] ++;
        FaceletPosition fp(ctrSide, edgeSide);
        vFacelet[ fp ] = Facelet(col, fp);
    }

    //Get FaceSide and Color for Corner Facelets and add them to array
    for(size_t i=0; i<4; i++){
        assertFaceSide(is, edgeSide );
        assertFaceSide(is, corSide );
        assertColor(is, col );
        aNumOfCol[col] ++;
        FaceletPosition fp(ctrSide, edgeSide, corSide);
        vFacelet[ fp ] = Facelet(col, fp);
    }

};

void Cube::createFaceFromLinearInput(std::istream &is, vecFacelet& vFacelet, arrNumber& aNumOfCol, arrBool& aIsSet ){
    FaceSide f;

    //Get front equivalent FaceSide
    assertFaceSide(is, f);

    //Get all equivalent FaceletPositions associated with given FaceSide
    listFletPos lfp = getEquivalentFletPos(f);

    //Creating Facelets and adding it to array
    for(const auto& fp: lfp){
        Color col;
        assertColor(is,col);

        aNumOfCol[col] ++;
        if(fp.getPositionType() == center)
            aIsSet[col] = true;

        vFacelet[ fp ] = Facelet(col, fp);
    }

};


void Cube::setOppColor(vecFacelet& vFacelet, arrColor& aOppColor){

    Facelet flF( vFacelet.at(FaceletPosition(front)) );
    Facelet flB( vFacelet.at(FaceletPosition(back)) );
    aOppColor[ flF.getColor() ] = flB.getColor();
    aOppColor[ flB.getColor() ] = flF.getColor();

    Facelet flU( vFacelet.at(FaceletPosition(up)) );
    Facelet flD( vFacelet.at(FaceletPosition(down)) );
    aOppColor[ flU.getColor() ] = flD.getColor();
    aOppColor[ flD.getColor() ] = flU.getColor();

    Facelet flL( vFacelet.at(FaceletPosition(left)) );
    Facelet flR( vFacelet.at(FaceletPosition(right)) );
    aOppColor[ flL.getColor() ] = flR.getColor();
    aOppColor[ flR.getColor() ] = flL.getColor();

}


void Cube::createCube(vecFacelet& vFacelet){
   
    //Create center Cubelets and add to array
    for( const auto& fs: {front, back, up, down, right, left} ){
        FaceletPosition fp(fs);
        CubeletPosition cp(fs);
        aCubelet[ cp ] = Cubelet( vFacelet[fp] );
    }


    //Create Edge Cubelets and add to array
    for( const auto& vfs: getEdgeFaceSide()){
        FaceletPosition fp1(vfs);
        FaceletPosition fp2(vfs[1], vfs[0]);
        CubeletPosition cp(vfs);
        aCubelet[ cp ] = Cubelet( vFacelet[fp1], vFacelet[fp2] );
    }


    //Create Corner Cubelets and add to array
    for( const auto& vfs: getCornerFaceSide()){
        FaceletPosition fp1(vfs);
        FaceletPosition fp2(vfs[1], vfs[0], vfs[2]);
        FaceletPosition fp3(vfs[2], vfs[0], vfs[1]);
        CubeletPosition cp(vfs);
        aCubelet[ cp ] = Cubelet( vFacelet[fp1], vFacelet[fp2], vFacelet[fp3] );
    }
}


CubeletPosition Cube::getCubeletPosition(std::size_t index){
    if( index > __NUM_CUBELET__ - 1 )
        throw std::out_of_range("Index: " + std::to_string(index) + " is not within range: [0, " + std::to_string(__NUM_CUBELET__) + ").");

    return vCletPos[ index ];
}

FaceletPosition Cube::getFaceletPosition(std::size_t index){
    if( index > __NUM_FACELET__ - 1 )
        throw std::out_of_range("Index: " + std::to_string(index) + " is not within range: [0, " + std::to_string(__NUM_FACELET__) + ").");

    return vFletPos[ index ];
}


Color Cube::getColorFromInt(std::size_t index){
    if( index > __NUM_FACE__ - 1 )
        throw std::out_of_range("Index: " + std::to_string(index) + " is not within range: [0, " + std::to_string(__NUM_FACE__) + ").");

    return vCol[ index ];
}

void Cube::show(const FaceSide& f){
    auto tlist = getEquivalentFletPos(f);
    auto it = tlist.begin();
    while( it != tlist.end()){
        for(int i=0;i<3;i++,it++){
            std::cout << getFacelet(*it).colorFormat() << " " ;
        }
        std::cout << std::endl;
    }
}


void Cube::rotateLayer(const FaceSide& f, bool is_clockwise, std::size_t no_of_turns , bool is_mid){

    //edge ( center if is_mid is true ) positions to operate on
    vecCletPos ve;
    //corner ( mid edge if is_mid is true ) positions to operate on
    vecCletPos vc;

    if(is_mid){
        ve = vecCenterEquivalence<CubeletPosition>(f);
        vc = vecMidEdgeEquivalence<CubeletPosition>(f);
    }else{
        ve = vecEdgeEquivalence<CubeletPosition>(f);
        vc = vecCornerEquivalence<CubeletPosition>(f);
    };

    no_of_turns %= 4;

    for(const auto& v:{ve,vc}){

        //Updating Cubelets at required position
        for(const auto& p:v){
            switch(no_of_turns){
                case 1:
                    aCubelet[p] *= (is_clockwise?f:opposite(f));
                    break;
                case 2:
                    aCubelet[p] *= (is_clockwise?f:opposite(f));
                    aCubelet[p] *= (is_clockwise?f:opposite(f));
                    break;
                case 3:
                    aCubelet[p] *= (!is_clockwise?f:opposite(f));
                    break;
                default:
                    break;
            }
        }

        //Relocating Cubelets to updated position
        std::size_t u = *v.begin();
        std::size_t r = *(v.begin()+1);
        std::size_t d = *(v.begin()+2);
        std::size_t l = *(v.begin()+3);

        switch(no_of_turns){
            case 1:
                std::swap(aCubelet[u], aCubelet[r]);
                if(is_clockwise){
                    std::swap(aCubelet[l], aCubelet[u]);
                    std::swap(aCubelet[d], aCubelet[l]);
                }else{
                    std::swap(aCubelet[d], aCubelet[r]);
                    std::swap(aCubelet[l], aCubelet[d]);
                }
                break;
            case 2:
                std::swap(aCubelet[u], aCubelet[d]);
                std::swap(aCubelet[r], aCubelet[l]);
                break;
            case 3:
                std::swap(aCubelet[u], aCubelet[r]);
                if(!is_clockwise){
                    std::swap(aCubelet[l], aCubelet[u]);
                    std::swap(aCubelet[d], aCubelet[l]);
                }else{
                    std::swap(aCubelet[d], aCubelet[r]);
                    std::swap(aCubelet[l], aCubelet[d]);
                }
                break;
            default:
                break;
        }

    }

}


void Cube::rotateSide(const FaceSide& f, bool is_clockwise, std::size_t no_of_turns){
    rotateLayer(f,is_clockwise,no_of_turns);
}
void Cube::rotateSide(const FaceSide& f, std::size_t no_of_turns, bool is_clockwise ){
    rotateLayer(f,is_clockwise,no_of_turns);
}


void Cube::rotateMid(const FaceSide& f, bool is_clockwise,std::size_t no_of_turns){
    rotateLayer(f,is_clockwise,no_of_turns,true);
}
void Cube::rotateMid(const FaceSide& f,std::size_t no_of_turns, bool is_clockwise){
    rotateLayer(f,is_clockwise,no_of_turns,true);
}


void Cube::rotate(const FaceSide& f,bool is_clockwise,std::size_t no_of_turns){
    rotate(f,no_of_turns,is_clockwise);
}
void Cube::rotate(const FaceSide& f,std::size_t no_of_turns,bool is_clockwise){
    FaceSide b = opposite(f);

    //rotate front  equivalent (i.e. given ) Face
    rotateSide(f,is_clockwise,no_of_turns);
    //rotate back equivalent (i.e. opposite of given) Face in the same absolute sense as in case of 'front equivalence'
    rotateSide(b,!is_clockwise,no_of_turns);
    //rotate mid equivalent layer
    rotateMid(f,no_of_turns,is_clockwise);
}



listFletPos getEquivalentFletPos(const FaceSide f){
    listFletPos tlist;
    FaceSide u,r,d,l;

    setEquivalentFaceSide(f,u,r,d,l);


    tlist.push_back({ f,l,u }); tlist.push_back({ f,u });   tlist.push_back({ f,r,u });
    tlist.push_back({ f,l });   tlist.push_back(f);         tlist.push_back({ f,r });
    tlist.push_back({ f,l,d }); tlist.push_back({ f,d });   tlist.push_back({ f,r,d });

    return tlist;
}


template <typename P>
std::vector<P> vecEdgeEquivalence(const FaceSide& f){

    FaceSide u,r,d,l;
    setEquivalentFaceSide(f,u,r,d,l);

    std::vector<P>   vpos;
    vpos.push_back( P(f,u) );
    vpos.push_back( P(f,r) );
    vpos.push_back( P(f,d) );
    vpos.push_back( P(f,l) );

    return vpos;
}

template std::vector<CubeletPosition> vecEdgeEquivalence<CubeletPosition>(const FaceSide& f);
template std::vector<FaceletPosition> vecEdgeEquivalence<FaceletPosition>(const FaceSide& f);


template <typename P>
std::vector<P> vecCornerEquivalence(const FaceSide& f){
    FaceSide u,r,d,l;
    setEquivalentFaceSide(f,u,r,d,l);

    std::vector<P>    vpos;
    vpos.push_back( P(f,u,l) );
    vpos.push_back( P(f,u,r) );
    vpos.push_back( P(f,d,r) );
    vpos.push_back( P(f,d,l) );

    return vpos;
}

template std::vector<CubeletPosition> vecCornerEquivalence<CubeletPosition>(const FaceSide& f);
template std::vector<FaceletPosition> vecCornerEquivalence<FaceletPosition>(const FaceSide& f);


template <typename P>
std::vector<P> vecCenterEquivalence(const FaceSide& f){
    FaceSide u,r,d,l;
    setEquivalentFaceSide(f,u,r,d,l);

    std::vector<P>    vpos;
    vpos.push_back( P(u) );
    vpos.push_back( P(r) );
    vpos.push_back( P(d) );
    vpos.push_back( P(l) );

    return vpos;

}


template <typename P>
std::vector<P> vecMidEdgeEquivalence(const FaceSide& f){
    FaceSide u,r,d,l;
    setEquivalentFaceSide(f,u,r,d,l);

    std::vector<P>    vpos;
    vpos.push_back( P(u,l) );
    vpos.push_back( P(u,r) );
    vpos.push_back( P(d,r) );
    vpos.push_back( P(d,l) );

    return vpos;
}
