/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 10th Apr 2017
 *
 * */

#include "position.h"
#include <iostream>
#include <algorithm>

std::ostream& operator<<(std::ostream &os, Step S)
{
    os << "side: " << S.f << ", is_clockwise: " << S.is_clockwise << ", no_of_turns: " << S.no_of_turns \
        << ", is_mid: " << S.is_mid ;
    return os;
}


template <> Color upper_limit(){ return undefcol; }
template <> FaceSide upper_limit(){ return undefside; }


template <typename E, bool _isFaceletType>
CollectionChild<E,_isFaceletType>::CollectionChild(E e1, E e2, E e3):
    CollectionChild<E,_isFaceletType>(typename std::vector<E>{e1,e2,e3})
{
}

template <typename E, bool B>
CollectionChild<E,B>::CollectionChild(std::vector<E> _ve):
    isFaceletType(B), _first(upper_limit<E>()), _second(upper_limit<E>()), _third(upper_limit<E>()), _num(0)
{
    // [Plan] Add support for vector of any size containing 3 or less valid FaceSides
    if( _ve.size()>3)
        throw std::runtime_error(std::string(__func__) + ": Vector size n must be, 0 < n <= 3.");
    if(_ve.size() >= 1) _first = _ve[0];
    if(_ve.size() >= 2) _second = _ve[1];
    if(_ve.size() == 3) _third = _ve[2];

    std::size_t max_limit = upper_limit<E>();
    _num += _first    != max_limit;
    _num += _second   != max_limit;
    _num += _third    != max_limit;
}

template <typename E, bool _isFaceletType>
CollectionChild<E,_isFaceletType>::operator std::size_t () const
{

#define ITR typename std::vector<E>::iterator

    std::size_t max_limit = upper_limit<E>();
    if(_first == max_limit)
        return -1;

    std::vector<E> vecE({_first,_second,_third});
    if(isFaceletType)
        std::sort(vecE.begin()+1,vecE.end());
    else
        std::sort(vecE.begin(),vecE.end());

    std::vector<E> vall = ::elements<E>();
    if(vecE[1]==max_limit && vecE[2]==max_limit)
    {
        std::size_t count = -1;
        for(ITR it0 = vall.begin(); it0 != vall.end(); it0++)
        {
            count++;
            if(*it0 == vecE[0])     return count;
        }
    }

    if(vecE[1]!=max_limit && vecE[2]==max_limit)
    {
        std::size_t count = 5;
        for(ITR it0 = vall.begin(); it0 != vall.end(); it0++)
        {
            ITR it1;
            if(isFaceletType)   it1 = vall.begin();
            else    it1 = it0+1;

            for(;it1 != vall.end(); it1 ++)
            {
                if(*it0 != *it1 && !are_opposite(*it0, *it1))   count++;
                if(vecE[0] == *it0 && vecE[1] == *it1)          return count;
            }
        }

    }

    if(vecE[1]!=max_limit && vecE[2]!=max_limit)
    {
        std::size_t count;
        if(isFaceletType)   count = 29;
        else                count = 17;
        for(ITR it0 = vall.begin(); it0 != vall.end(); it0++)
        {
            ITR it1;
            if(isFaceletType)   it1 = vall.begin();
            else                it1 = it0+1;

            for(;it1 != vall.end(); it1 ++)
            {
                for(ITR it2 = it1+1; it2 != vall.end(); it2++)
                {
                    if(!any_same(*it0,*it1,*it2) && !any_opposite(*it0,*it1,*it2))  count++;
                    if(vecE[0] == *it0 && vecE[1] == *it1 && vecE[2] == *it2)       return count;
                }
            }
        }
    }
        

    return -1;

#undef  ITR

}


template <typename E, bool B>
bool operator==(const CollectionChild<E,B>& lhs, const CollectionChild<E,B>& rhs){
    std::size_t lt = lhs;
    std::size_t rt = rhs;
    return (lt==rt);
}

template <bool _isFaceletType>
CollectionWrapper<FaceSide,_isFaceletType>::CollectionWrapper(std::vector<FaceSide> v):
    CollectionChild<FaceSide,_isFaceletType>(v),
    _first(CollectionChild<FaceSide,_isFaceletType>::_first),
    _second(CollectionChild<FaceSide,_isFaceletType>::_second),
    _third(CollectionChild<FaceSide,_isFaceletType>::_third),
    _num(CollectionChild<FaceSide,_isFaceletType>::_num)
{
    if(any_opposite(_first,_second,_third))
        throw std::runtime_error(std::string(__func__) + ": opposite elements present.");

    if(_num==0)
        _ptype = undeftype;
    else
    {
        std::vector<PositionType> v = ::elements<PositionType>();
        _ptype = v[_num-1];
    }
}

template <bool B>
CollectionWrapper<FaceSide,B>::CollectionWrapper(const CollectionWrapper<FaceSide,B>& cw):
    CollectionWrapper(cw.all())
{}

template <bool B>
CollectionWrapper<FaceSide,B>& CollectionWrapper<FaceSide,B>::operator=(CollectionWrapper<FaceSide,B> cw)
{
    std::swap(_ptype, cw._ptype);
    std::swap(_first, cw._first);
    std::swap(_second, cw._second);
    std::swap(_third, cw._third);
    std::swap(_num, cw._num);
    return *this;
}

template <bool B>
CollectionWrapper<FaceSide, B> CollectionWrapper<FaceSide,B>::relative(const FaceSide& f) const{
    std::vector<FaceSide> vFS;
    for(const auto& fs: {_first,_second,_third})
        vFS.push_back( getRelativeFaceSide(fs, f) );

    return vFS;
}

template <bool B>
bool CollectionWrapper<FaceSide,B>::affectable(Step s) const
{
    ///If faceside is not defined then roatation itself is not defined, return false
    if(s.f == undefside)
        return false;

    ///Return true when Position is on the Face being roated
    if(s.is_mid==false && isOn(s.f))
        return true;

    ///Return true when Position is on the Middle layer being roated
    if(s.is_mid==true && !isOn(s.f) && !isOn( opposite(s.f) ))
        return true;

    ///Other wise return false
    return false;
}

template <bool B>
CollectionWrapper<FaceSide,B> CollectionWrapper<FaceSide,B>::result(StepSequence seq) const
{
    CollectionWrapper<FaceSide,B> pRet(_first,_second,_third);

    for(const auto& s: seq)
        for(std::size_t turns = 1; turns <= s.no_of_turns; turns++)
            if(s.f != undefside && pRet.affectable(s))
                pRet *= (s.is_clockwise ? s.f : opposite(s.f) );

    return pRet;
}

template <bool B>
CollectionWrapper<FaceSide,B>& CollectionWrapper<FaceSide,B>::operator*=(const FaceSide& rhs){
    if(rhs == undefside )
        throw std::runtime_error(__func__ + std::string(": Position multiplication with undefside is not allowed"));
    _first *= rhs;
    _second *= rhs;
    _third *= rhs;
    return *this;
}

template <bool B>
std::ostream& operator<<(std::ostream& os, CollectionWrapper<FaceSide,B> P){
    os << "Position: ptype = " << P._ptype;
    os << ", vecSide = { ";
    for(const auto& face : P.all()){
        if(face != undefside)
            os << face << " ";
    }
    os << "}";
    return os;
}


template class CollectionWrapper<FaceSide,true>;
template class CollectionWrapper<FaceSide,false>;
template bool operator==<FaceSide,true>(const CollectionChild<FaceSide,true>&, const CollectionChild<FaceSide,true>&);
template bool operator==<FaceSide,false>(const CollectionChild<FaceSide,false>&, const CollectionChild<FaceSide,false>&);
template std::ostream& operator<< <true>(std::ostream&, CollectionWrapper<FaceSide,true>);
template std::ostream& operator<< <false>(std::ostream&, CollectionWrapper<FaceSide,false>);
