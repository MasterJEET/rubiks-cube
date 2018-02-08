/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 8th Jun 2017
 *
 * */

#include "cube.h"
#include "cuception.h"
#include <iterator>

vecCletPos Cube::vCletPos (__NUM_CUBELET__);
vecFletPos Cube::vFletPos (__NUM_FACELET__);
std::vector<Color> Cube::vCol (__NUM_FACE__);
std::size_t Cube::num_of_instances = 0;


Cube::Cube()
{

    std::stringstream ss;

    ss << "# The input depicted here is of fully solved Cube" << std::endl;

    ss << "F: W W W W W W W W W" << std::endl;

    ss << "B: Y Y Y Y Y Y Y Y Y" << std::endl;

    ss << "L: O O O O O O O O O    //Just testing different type of comment" << std::endl;

    ss << "R: R R R R R R R R R" << std::endl;

    ss << "U: B B B B B B B B B    /This comment should also get ignored" << std::endl;

    ss << "D: G G G G G G G G G" << std::endl;

    enInputFormat eifX = LINEAR_FORMAT;
    init(ss, eifX);

}

Cube::Cube(std::istream &is, enInputFormat eifX) {
    init(is, eifX);
}


Cube::Cube(std::string file_path, enInputFormat eifX) {

    std::ifstream ifs;
    ifs.open(file_path);
    if(!ifs)
        throw std::runtime_error("Could not open file: \"" + file_path + "\".");
    init(ifs, eifX);

}


void Cube::init(std::istream& is, enInputFormat eifX){

    num_of_instances ++;

    if(num_of_instances == 1){
        mapIntToCubeletPosition();
        mapIntToFaceletPosition();
        mapIntToColor();
    }
    
    //Array for storing Facelets with FaceletPosition as key
    vecFacelet vFacelet(__NUM_FACELET__);
    
    //Keep track of number of each valid (not undefside) Colors encountered
    arrNumber aNumOfCenterCol{0,0,0,0,0,0};
    
    //Keep track of number of each valid (not undefside) Colors encountered on edge Facelets
    arrNumber aNumOfEdgeCol{0,0,0,0,0,0};

    //Keep track of number of each valid (not undefside) Colors encountered on corner Facelets
    arrNumber aNumOfCornerCol{0,0,0,0,0,0};

    ///Get all Faces
    switch(eifX){

        case LINEAR_FORMAT:
            for(int i=0; i < __NUM_FACE__ ; i++)
                createFaceFromLinearInput(is, vFacelet, aNumOfCenterCol, aNumOfEdgeCol, aNumOfCornerCol);
            break;

        case STEP_FORMAT:
            for(int i=0; i < __NUM_FACE__ ; i++)
                createFaceFromStepInput(is, vFacelet, aNumOfCenterCol, aNumOfEdgeCol, aNumOfCornerCol);
            break;

        default:
            throw std::runtime_error("Input format not recognized.");

    }

    ///Check if all required Facelets are created
    vecFacelet::const_iterator iter = std::find( std::begin(vFacelet), std::end(vFacelet), Facelet() );
    if( iter != std::end(vFacelet) )
        throw NumOfFaceletException(  iter - vFacelet.begin() );

    setOppColor(vFacelet);


    validateEdgeColor(vFacelet);


    validateCornerColor(vFacelet);


    validateNumOfColor(aNumOfCenterCol, aNumOfEdgeCol, aNumOfCornerCol);

    ///Create Cubelets from vecFacelet and store it in Cubelet array
    createCube(vFacelet);

}


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


void Cube::validateEdgeColor(vecFacelet& vFacelet){

    for(const auto& vfs: getEdgeFaceSide())
    {
        FaceletPosition fp1(vfs);
        FaceletPosition fp2( vfs[1], vfs[0] );

        Facelet f1( vFacelet[fp1] );
        Facelet f2( vFacelet[fp2] );

        bool are_same = f1.getColor() == f2.getColor();
        if(are_same)
            throw EdgeColorException(vfs, "Same Color present.");

        bool are_opp = aOppColor[ f1.getColor() ] == f2.getColor();
        if(are_opp)
            throw EdgeColorException(vfs, "Opposite Color present.");
    }

}


void Cube::validateCornerColor(vecFacelet& vFacelet){

    for(const auto& vfs: getCornerFaceSide())
    {
        FaceletPosition fp1(vfs);
        FaceletPosition fp2( vfs[1], vfs[0], vfs[2] );
        FaceletPosition fp3( vfs[2], vfs[0], vfs[1] );

        Facelet f1( vFacelet[fp1] );
        Facelet f2( vFacelet[fp2] );
        Facelet f3( vFacelet[fp3] );

        bool are_same = f1.getColor() == f2.getColor();
        are_same = are_same || (f2.getColor() == f3.getColor());
        are_same = are_same || (f3.getColor() == f1.getColor());
        if(are_same)
            throw CornerColorException( CubeletPosition(vfs) ,"Same Color present.");

        bool are_opp = anyOppColor( f1.getColor(), f2.getColor(), f3.getColor() );
        if(are_opp)
            throw CornerColorException( vfs , "Opposite Color present.");
    }

}


void Cube::validateNumOfColor(
        arrNumber& aNumOfCenterCol,
        arrNumber& aNumOfEdgeCol,
        arrNumber& aNumOfCornerCol
){

    for(std::size_t i=0; i < __NUM_FACE__; i++ )
    {
        std::size_t num_ctr = aNumOfCenterCol[i];
        std::size_t num_edg = aNumOfEdgeCol[i];
        std::size_t num_cnr = aNumOfCornerCol[i];
        if(num_ctr != 1 || num_edg != 4 || num_cnr != 4){
            throw NumOfColorException(i, num_ctr, num_edg, num_cnr);
        }
    }

};


void Cube::createFaceFromStepInput(
        std::istream &is,
        vecFacelet& vFacelet,
        arrNumber& aNumOfCenterCol,
        arrNumber& aNumOfEdgeCol,
        arrNumber& aNumOfCornerCol
){

    FaceSide ctrSide, edgeSide, corSide;
    Color col;

    //Get FaceSide and Color for Center Facelet
    assertFaceSide(is, ctrSide );
    assertColor(is, col );

    aNumOfCenterCol[col] ++;
    //aFaceSide[col] = ctrSide;

    //Create Center Facelet and add it to array
    vFacelet[ FaceletPosition(ctrSide) ] = Facelet(col, ctrSide);

    //Get FaceSide and Color for Edge Facelets and add them to array
    for(size_t i=0; i<4; i++){
        assertFaceSide(is, edgeSide );
        assertColor(is, col);
        aNumOfEdgeCol[col] ++;
        FaceletPosition fp(ctrSide, edgeSide);
        vFacelet[ fp ] = Facelet(col, fp);
    }

    //Get FaceSide and Color for Corner Facelets and add them to array
    for(size_t i=0; i<4; i++){
        assertFaceSide(is, edgeSide );
        assertFaceSide(is, corSide );
        assertColor(is, col );
        aNumOfCornerCol[col] ++;
        FaceletPosition fp(ctrSide, edgeSide, corSide);
        vFacelet[ fp ] = Facelet(col, fp);
    }

};

void Cube::createFaceFromLinearInput(
        std::istream &is,
        vecFacelet& vFacelet,
        arrNumber& aNumOfCenterCol,
        arrNumber& aNumOfEdgeCol,
        arrNumber& aNumOfCornerCol
){
    FaceSide f;

    //Get front equivalent FaceSide
    assertFaceSide(is, f);

    //Get all equivalent FaceletPositions associated with given FaceSide
    listFletPos lfp = getEquivalentFletPos(f);

    //Creating Facelets and adding it to array
    for(const auto& fp: lfp){
        Color col;
        assertColor(is,col);

        switch(fp.getPositionType()){
            case center:
                aNumOfCenterCol[col] ++;
                //aFaceSide[col] = fp.getSideAt(0);
                break;
            case edge:
                aNumOfEdgeCol[col] ++;
                break;
            case corner:
                aNumOfCornerCol[col] ++;
                break;
            case undeftype:
                break;
        }

        vFacelet[ fp ] = Facelet(col, fp);
    }

};


void Cube::setOppColor(vecFacelet& vFacelet){

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


bool Cube::areOppColor(const Color& first, const Color& second) const{
    return aOppColor[ first ] == second;
}


bool Cube::anyOppColor(const Color& c1, const Color& c2, const Color& c3) const{
    bool are_opp = aOppColor[ c1 ] == c2;
    are_opp = are_opp || ( aOppColor[ c2 ] == c3 );
    are_opp = are_opp || ( aOppColor[ c3 ] == c1 );
    return are_opp;
}


//FaceSide Cube::getSideOfColor(const Color& c){
//    if(c == undefcol)
//        return undefside;
//    return aFaceSide[ c ];
//}


std::size_t Cube::ColorSetToInt(const ColorSet& cs) const{

    //if only one Color is defined, return it
    if(cs.mid() == undefcol && cs.max() == undefcol)
        return cs.min();


    //When only two Colors defined
    if( cs.mid() != undefcol && cs.max() == undefcol )
    {
        if( areOppColor(cs.min(), cs.mid() ) )
            throw std::runtime_error(std::string() + __func__+ ": Two defined Colors in ColorSet are opposite.");


        //No need to sort elements as the elements are already
        //sorted in ColorSet

        std::size_t ret = 0;
        for( std::size_t min = 0; min < __NUM_FACE__ ; min++ )
            for( std::size_t mid = min + 1; mid < __NUM_FACE__ ; mid++ )
            {
                if( !areOppColor( vCol[min], vCol[mid] ) && mid != min )
                    ret++;

                if( vCol[mid] == cs.mid() && vCol[min] == cs.min() )
                    return 5 + ret;
            }

    }


    //When all the three Colors are defined in ColorSet
    if( cs.mid() != undefcol && cs.max() != undefcol )
    {
        if( anyOppColor(cs.min(), cs.mid(), cs.max()) )
            throw std::runtime_error(std::string() + __func__ + ": At least two among three defined Colors are opposite.");

        //No need to sort elements as the elements are already
        //sorted in ColorSet

        std::size_t ret = 0;
        for( std::size_t min = 0; min < __NUM_FACE__ ; min++ )
            for( std::size_t mid = min + 1; mid < __NUM_FACE__ ; mid++ )
                for( std::size_t max = mid + 1; max < __NUM_FACE__ ; max++ )
                {
                    //If there are no opposite or same Colors, increment count
                    if( !anyOppColor( vCol[min], vCol[mid], vCol[max] ) &&\
                            ( vCol[min] != vCol[mid] && vCol[mid] != vCol[max] && vCol[max] != vCol[min] ) )
                        ret++;

                    if( vCol[min] == cs.min() && vCol[mid] == cs.mid() && vCol[max] == cs.max() )
                        return 17 + ret;
                }

    }


    //Execution will never reach here
    return -1;
}


std::size_t Cube::ColorSetToInt(const CubeletPosition& cp) const
{
    std::vector<Color> vColor;
    for(const auto& fl: aCubelet[cp].getFacelet() )
        vColor.push_back( fl.getColor() );

    return ColorSetToInt(vColor);
}


//void Cube::setEquivalentColor(
//        const Color& cFront,
//        Color& cUp,
//        Color& cRight,
//        Color& cDown,
//        Color& cLeft
//        )
//{
//    FaceSide f = getSideOfColor( cFront );
//    FaceSide u,r,d,l;
//    setEquivalentFaceSide(f,u,r,d,l);
//    cUp     = getFacelet( u ).getColor();
//    cRight  = getFacelet( r ).getColor();
//    cDown   = getFacelet( d ).getColor();
//    cLeft   = getFacelet( l ).getColor();
//}


//std::size_t Cube::ColorSetToInt(const ColorSet& cs){
//    
//    if(cs.mid() == undefside && cs.max() == undefside)
//        return cs.min();
//
//    if(cs.mid() != undefside && cs.max() == undefside)
//    {
//        bool are_opp = areOppColor( cs.min(), cs.mid() );
//        if(are_opp)
//            throw std::runtime_error(std::string() + __func__ + "Two defined Colors,in ColorSet, are opposite.");
//        if(cs.min()
//    }
//}


void Cube::createCube(vecFacelet& vFacelet){
   
    //Create center Cubelets and add to array
    for( const auto& fs: {front, back, up, down, right, left} ){
        FaceletPosition fp(fs);
        CubeletPosition cp(fs);
        aCubelet[ cp ] = Cubelet( vFacelet[fp] );
        aCletPos[ ColorSetToInt(cp) ] = cp;
    }


    //Create Edge Cubelets and add to array
    for( const auto& vfs: getEdgeFaceSide()){
        FaceletPosition fp1(vfs);
        FaceletPosition fp2(vfs[1], vfs[0]);
        CubeletPosition cp(vfs);
        aCubelet[ cp ] = Cubelet( vFacelet[fp1], vFacelet[fp2] );
        aCletPos[ ColorSetToInt(cp) ] = cp;
    }


    //Create Corner Cubelets and add to array
    for( const auto& vfs: getCornerFaceSide()){
        FaceletPosition fp1(vfs);
        FaceletPosition fp2(vfs[1], vfs[0], vfs[2]);
        FaceletPosition fp3(vfs[2], vfs[0], vfs[1]);
        CubeletPosition cp(vfs);
        aCubelet[ cp ] = Cubelet( vFacelet[fp1], vFacelet[fp2], vFacelet[fp3] );
        aCletPos[ ColorSetToInt(cp) ] = cp;
    }
}


CubeletPosition Cube::getCubeletPosition(std::size_t index){
    if( index > __NUM_CUBELET__ - 1 )
        throw std::out_of_range("Index: " + std::to_string(index) +\
                " is not within range: [0, " + std::to_string(__NUM_CUBELET__) + ").");

    return vCletPos[ index ];
}

FaceletPosition Cube::getFaceletPosition(std::size_t index){
    if( index > __NUM_FACELET__ - 1 )
        throw std::out_of_range("Index: " + std::to_string(index) +\
                " is not within range: [0, " + std::to_string(__NUM_FACELET__) + ").");

    return vFletPos[ index ];
}


Color Cube::getColorFromInt(std::size_t index){
    if( index > __NUM_FACE__ - 1 )
        throw std::out_of_range("Index: " + std::to_string(index) +\
                " is not within range: [0, " + std::to_string(__NUM_FACE__) + ").");

    return vCol[ index ];
}

//void Cube::show(const FaceSide& f){
//    auto tlist = getEquivalentFletPos(f);
//    auto it = tlist.begin();
//    while( it != tlist.end()){
//        for(int i=0;i<3;i++,it++){
//            std::cout << getFacelet(*it).colorFormat() << " " ;
//        }
//        std::cout << std::endl;
//    }
//}


void Cube::helper(const CubeletPosition& cp, FaceSide f, std::size_t n)
{
    for(std::size_t i = 0; i<n; i++)
    {
        aCubelet[cp] *= f;
        aCletPos[ ColorSetToInt(cp) ] *= f;
    }
}


void Cube::rotateLayer(const FaceSide& f, bool is_clockwise, std::size_t no_of_turns , bool is_mid){

    //Do nothing if FaceSide is not specified
    if(f==undefside)return;

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
            FaceSide fs;
            switch(no_of_turns){
                case 1:
                    fs = (is_clockwise?f:opposite(f));
                    helper(p,fs);
                    break;
                case 2:
                    fs = (is_clockwise?f:opposite(f));
                    helper(p,fs,2);
                    break;
                case 3:
                    fs = (!is_clockwise?f:opposite(f));
                    helper(p,fs);
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


void Cube::rotateSide(){
    rotateLayer(front,true,1);
}
void Cube::rotateSide(const FaceSide& f){
    rotateLayer(f,true,1);
}
void Cube::rotateSide(const FaceSide& f, std::size_t no_of_turns){
    rotateLayer(f,true,no_of_turns);
}
void Cube::rotateSide(const FaceSide& f, int no_of_turns){
    rotateLayer(f,true,no_of_turns);
}
void Cube::rotateSide(const FaceSide& f, bool is_clockwise){
    rotateLayer(f,is_clockwise,1);
}
void Cube::rotateSide(const FaceSide& f, bool is_clockwise, std::size_t no_of_turns){
    rotateLayer(f,is_clockwise,no_of_turns);
}
void Cube::rotateSide(const FaceSide& f, std::size_t no_of_turns, bool is_clockwise ){
    rotateLayer(f,is_clockwise,no_of_turns);
}
void Cube::rotateSide(Step s){
    rotateLayer(s.f, s.is_clockwise, s.no_of_turns);
}


void Cube::rotateMid(){
    rotateLayer(front,true,1,true);
}
void Cube::rotateMid(const FaceSide& f){
    rotateLayer(f,true,1,true);
}
void Cube::rotateMid(const FaceSide& f, std::size_t no_of_turns){
    rotateLayer(f,true,no_of_turns,true);
}
void Cube::rotateMid(const FaceSide& f, int no_of_turns){
    rotateLayer(f,true,no_of_turns,true);
}
void Cube::rotateMid(const FaceSide& f, bool is_clockwise){
    rotateLayer(f,is_clockwise,1,true);
}
void Cube::rotateMid(const FaceSide& f, std::size_t no_of_turns, bool is_clockwise){
    rotateLayer(f,is_clockwise,no_of_turns,true);
}
void Cube::rotateMid(const FaceSide& f, bool is_clockwise, std::size_t no_of_turns){
    rotateLayer(f,is_clockwise,no_of_turns,true);
}
void Cube::rotateMid(Step s){
    rotateLayer(s.f, s.is_clockwise, s.no_of_turns, true);
}


void Cube::rotate(){
    rotate(front,1,true);
}
void Cube::rotate(const FaceSide& f){
    rotate(f,1,true);
}
void Cube::rotate(const FaceSide& f, std::size_t no_of_turns){
    rotate(f,no_of_turns,true);
}
void Cube::rotate(const FaceSide& f, int no_of_turns){
    rotate(f,no_of_turns,true);
}
void Cube::rotate(const FaceSide& f, bool is_clockwise){
    rotate(f,1,is_clockwise);
}
void Cube::rotate(const FaceSide& f,bool is_clockwise,std::size_t no_of_turns){
    rotate(f,no_of_turns,is_clockwise);
}
void Cube::rotate(const FaceSide& f,std::size_t no_of_turns,bool is_clockwise){
    FaceSide b = opposite(f);

    //rotate front  equivalent (i.e. given ) Face
    rotateSide(f,is_clockwise,no_of_turns);
    //rotate back equivalent (i.e. opposite of given) Face in the
    //same absolute sense as in case of 'front equivalence'
    rotateSide(b,!is_clockwise,no_of_turns);
    //rotate mid equivalent layer
    rotateMid(f,no_of_turns,is_clockwise);
}
void Cube::rotate(Step s){
    rotate(s.f, s.no_of_turns, s.is_clockwise);
}
void Cube::rotate(StepSequence seq){
    for(const auto& s : seq)
        rotate(s.f, s.no_of_turns, s.is_clockwise);
}


void Cube::update(StepSequence seq){
    for(StepSequence::iterator it = seq.begin(); it != seq.end(); it++)
        if(!it->is_mid)
            rotateLayer(it->f, it->is_clockwise, it->no_of_turns);
        else
            rotateLayer(it->f, it->is_clockwise, it->no_of_turns, true);
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


FaceletColor::operator std::size_t () const
{
    ///In FaceletColor, first Color must be defined
    if(col1 == undefcol)
        return -1;

    //Here we have col1 defined. rest two cols can be anything
    ///If there's only undefcol in last two cols then put it to last.
    Color tmp1 = col1;
    Color tmp2 = col2;
    Color tmp3 = col3;
    if( tmp2 == undefcol && tmp3 != undefcol )
        std::swap(tmp2, tmp3);

    ///1. Colors are enum (integer). if there's only one defined that.
    ///Each Color is assigned a Color between [0 5].
    if( tmp2 == undefcol && tmp3 == undefcol )
        return tmp1;

    ///2. if two Colors are defined, count possible arrangements sequenctially.
    ///When there is a match between possible arrangement and given arrangement (FaceletColor) add the
    ///count to previous (step #1) count max (i.e. 5).
    if ( tmp2 != undefcol && tmp3 == undefcol )
    {

        std::size_t count = 0;

        for( std::size_t i1 = 0; i1 < __NUM_FACE__ ; i1++ )
            for( std::size_t i2 = 0; i2 < __NUM_FACE__ ; i2++ )
            {
                if( !cube.areOppColor( Cube::vCol[i1], Cube::vCol[i2] ) && i2 != i1 )
                {
                    count++;
                    if( Cube::vCol[i2] == tmp2 && Cube::vCol[i1] == tmp1 )
                        return 5 + count;
                }

            }

    }


    ///3. If all the three Colors are defined, count as in Step #2. When there's a match add the count to total number of valid
    ///valid configuration seen so far including the ones in step #1 and step #2.
    if ( tmp2 != undefcol && tmp3 != undefcol )
    {
        //sort second and third Color (put larger one to last), this is necessary make their order irrelevant
        if(tmp2 > tmp3)
            std::swap(tmp2,tmp3);

        std::size_t count = 0;
        for( std::size_t i1 = 0; i1 < __NUM_FACE__ ; i1++ )
            for( std::size_t i2 = 0; i2 < __NUM_FACE__ ; i2++ )
                for( std::size_t i3 = i2 + 1; i3 < __NUM_FACE__ ; i3++ )
                {
                    //If there are no opposite or same Colors, increment count
                    if( !cube.anyOppColor( Cube::vCol[i1], Cube::vCol[i2], Cube::vCol[i3] ) &&\
                            ( Cube::vCol[i1] != Cube::vCol[i2] && Cube::vCol[i2] != Cube::vCol[i3] && Cube::vCol[i3] != Cube::vCol[i1] ) )
                    {
                        count++;
                        if( Cube::vCol[i1] == tmp1 && Cube::vCol[i2] == tmp2 && Cube::vCol[i3] == tmp3 )
                            return 29 + count;
                    }
                }
    }


    ///If doesn't belong to above categories then retrun -1 indicating a failure
    return -1;
}
