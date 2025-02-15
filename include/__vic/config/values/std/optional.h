// Value parser for std::optional
//
// Platform: ISO C++ 17
// $Id$
//
// (c) __vic 2019

#ifndef __VIC_CONFIG_VALUES_STD_OPTIONAL_H
#define __VIC_CONFIG_VALUES_STD_OPTIONAL_H

#include<__vic/config/value.h>
#include<optional>

namespace __vic { namespace config {

//////////////////////////////////////////////////////////////////////////////
template<class T>
struct value<std::optional<T>>
{
    static bool parse(const std::string &s, std::optional<T> &res)
    {
        T v;
        if(!value<T>::parse(s, v)) return false;
        res = std::move(v);
        return true;
    }
};
//////////////////////////////////////////////////////////////////////////////
template<class T, class Parser>
class complex_value<std::optional<T>, Parser, false> :
    public abstract_complex_value
{
    std::optional<T> *pValue;
public:
    explicit complex_value(std::optional<T> &v) : pValue(&v) {}
    using abstract_complex_value::parse;
    void parse(source &s) final
    {
        Parser p(pValue->emplace());
        s.read(p);
    }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
