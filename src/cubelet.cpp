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

    std::sort(lhsCol.begin(),lhsCol.end());
    std::sort(rhsCol.begin(),rhsCol.end());

    return lhsCol == rhsCol;

}


Cubelet& Cubelet::operator*=(const FaceSide& rhs){
    if(rhs == undefside)
        throw std::runtime_error(__func__ + std::string(": Cubelet multiplication with undefside is not allowed."));

    for(auto& fl: vFacelet)
        fl *= rhs;

    pos *= rhs;
    return *this;
}
