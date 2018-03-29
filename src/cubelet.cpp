/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 13th Apr 2017
 *
 * */

#include "cubelet.h"
#include <iterator>     //std::begin, std::end


FaceSide getCommonFace(const CubeletPosition& first, const CubeletPosition& second)
{
    for(const auto& f: first.all())
        for(const auto& s: second.all())
            if(f == s)
                return f;
    return undefside;
}


bool areClockwise(const CubeletPosition& from, const CubeletPosition& to, const FaceSide& f)
{
    //Query is valid only for Corner CubeletPositions
    if(from.num() == 2 && to.num() == 2)
        return true;

    if( !from.isOn(f) || !to.isOn(f) )
        throw std::runtime_error(__func__ + std::string(": Both the position must be on given FaceSide."));

    CubeletPosition cpTmp(from*f);

    return (cpTmp == to);
}


SetOfColor::SetOfColor(Color c1,Color c2, Color c3):
    col_min(c1), col_mid(c2), col_max(c3)
{
    init();
}

SetOfColor::SetOfColor(std::vector<Color> vColor):
    col_mid(undefcol), col_max(undefcol)
{
    if( vColor.size() == 0 || vColor.size() > 3 )
        throw std::runtime_error(std::string() + __func__ + ": vector<Color> size can only be 1, 2 or 3." );
    col_min = vColor[0];
    if(vColor.size() > 1)
        col_mid = vColor[1];
    if(vColor.size() == 3)
        col_max = vColor[2];

    init();
}

void SetOfColor::init(){
    if( col_min > col_mid )
        std::swap(col_min, col_mid);
    if( col_mid > col_max )
        std::swap(col_mid, col_max);
    if( col_min > col_mid )
        std::swap(col_min, col_mid);

    //At least one Color must be defined, it'll automatically
    //be present in col_min due above check & swap
    if( col_min == undefcol )
        throw std::runtime_error(std::string() + __func__ + ": At least one Color must be defined.");

    //Color must not be same
    if( col_mid != undefcol && col_max == undefcol && col_min == col_mid)
        throw std::runtime_error(std::string() + __func__ + ": Two defined Colors are same.");
    if( ( col_mid != undefcol && col_max != undefcol ) &&\
            ( col_min == col_mid || col_mid == col_max || col_max == col_min ) )
        throw std::runtime_error(std::string() + __func__ + ": At least two among three defined Colors are same.");
}

Cubelet::Cubelet(std::vector<Facelet> _vecFac): vFacelet(_vecFac) {
    switch( _vecFac.size() ){
        case 1:
            {
            pos = CubeletPosition( _vecFac[0].getPosition().all() );
            break;
            }
        case 2:
            {
            CubeletPosition cp1(_vecFac[0].getPosition().all() );
            CubeletPosition cp2(_vecFac[1].getPosition().all() );
            if(cp1 != cp2)
                throw std::runtime_error(std::string() + __func__ + ": Two Facelets provided doesnot belong to same Cubelet");
            pos = cp1 ;
            break;
            }
        case 3:
            {
            CubeletPosition cp1(_vecFac[0].getPosition().all() );
            CubeletPosition cp2(_vecFac[1].getPosition().all() );
            CubeletPosition cp3(_vecFac[2].getPosition().all() );
            if(cp1 != cp2 || cp1 != cp3 || cp2 != cp3)
                throw std::runtime_error(std::string() + __func__ + ": Three Facelets provided doesnot belong to same Cubelet");
            pos = cp1;
            break;
            }
        default:
            throw std::runtime_error(std::string() + __func__ + ": _vecFac can only have size such that 0 < size <= 3...");
            
    }
}

listFletPos Cubelet::getEquivalentFletPosList() const{
    listFletPos lFaceletPosition;

    if(pos.num() == 1)
        lFaceletPosition.push_back( pos.first() );

    if(pos.num() == 2){
        lFaceletPosition.push_back({ pos.first(), pos.second() });
        lFaceletPosition.push_back({ pos.second(), pos.first() });
    }

    if(pos.num() == 3){
        lFaceletPosition.push_back({ pos.first(), pos.second(), pos.third() });
        lFaceletPosition.push_back({ pos.second(), pos.third(), pos.first() });
        lFaceletPosition.push_back({ pos.third(), pos.first(), pos.second() });
    }

    return lFaceletPosition;
};

vecFacelet Cubelet::getFacelet() const{
    return vFacelet;
}

Facelet Cubelet::getFacelet(const FaceletPosition& fp) const{
    CubeletPosition cp(fp.all());
    if(cp != pos)
        throw std::out_of_range(std::string() + __func__ + ": Requested Facelet is not in this Cubelet. Check your FaceletPosition.");

    Facelet f_ret;
    for(const auto& f_tmp : vFacelet){
        if(f_tmp.getPosition() == fp){
            f_ret = f_tmp;
            break;
        }
    }
    return f_ret;
}

std::ostream& operator<<(std::ostream& os, Cubelet C){
    os << "Facelet(s): {";

    for(const auto& flet: C.vFacelet)
        os << " (" << flet.side() << ", " << flet.getColor() << ") ";

    os << "}";
    return os;
}

bool operator==(const Cubelet& lhs, const Cubelet& rhs){
    if( lhs.pos != rhs.pos)
        return false;

    for(const auto& fp: lhs.getEquivalentFletPosList()){
        if(lhs.getFacelet(fp) != rhs.getFacelet(fp))
            return false;
    }

    return true;
}


bool haveSameColors(const Cubelet& lhs, const Cubelet& rhs)
{
    std::vector<Color> lhsCol;
    std::vector<Color> rhsCol;

    for(const auto& fl: lhs.getFacelet())
        lhsCol.push_back(fl.getColor());
    for(const auto& fl: rhs.getFacelet())
        rhsCol.push_back(fl.getColor());

    SetOfColor lhscs(lhsCol);
    SetOfColor rhscs(rhsCol);

    return lhscs == rhscs;

}


Cubelet& Cubelet::operator*=(const FaceSide& rhs){
    if(rhs == undefside)
        throw std::runtime_error(__func__ + std::string(": Cubelet multiplication with undefside is not allowed."));

    for(auto& fl: vFacelet)
        fl *= rhs;

    pos *= rhs;
    return *this;
}
