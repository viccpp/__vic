//
// $Id$
//

#if __cplusplus >= 201103L // C++11

#include<__vic/config/value.h>
#include<__vic/string_utils.h>
#include<__vic/str2num.h>
#include<__vic/ascii_string.h>

namespace __vic { namespace config {

namespace {
//----------------------------------------------------------------------------
template<class TInt>
inline bool to_number_(const std::string &s, TInt &v)
{
    number_parse_result<TInt> r = parse_decimal<TInt>(s);
    if(!r) return false;
    v = r.value();
    return true;
}
//----------------------------------------------------------------------------
} // namespace

bool abstract_value::is_list() const { return false; }
void abstract_atom_value::parse(source & ) {}
bool abstract_complex_value::parse(const std::string & ) { return false; }
bool abstract_atom_value::is_complex() const { return false; }
bool abstract_complex_value::is_complex() const { return true; }
bool abstract_atom_list_value::is_list() const { return true; }
bool abstract_complex_list_value::is_list() const { return true; }

//----------------------------------------------------------------------------
bool value<signed char>::parse(const std::string &v, signed char &res)
{
    return to_number_(v, res);
}
//----------------------------------------------------------------------------
bool value<short>::parse(const std::string &v, short &res)
{
    return to_number_(v, res);
}
//----------------------------------------------------------------------------
bool value<int>::parse(const std::string &v, int &res)
{
    return to_number_(v, res);
}
//----------------------------------------------------------------------------
bool value<long>::parse(const std::string &v, long &res)
{
    return to_number_(v, res);
}
//----------------------------------------------------------------------------
bool value<long long>::parse(const std::string &v, long long &res)
{
    return to_number_(v, res);
}
//----------------------------------------------------------------------------
bool value<unsigned char>::parse(const std::string &v, unsigned char &res)
{
    return to_number_(v, res);
}
//----------------------------------------------------------------------------
bool value<unsigned short>::parse(const std::string &v, unsigned short &res)
{
    return to_number_(v, res);
}
//----------------------------------------------------------------------------
bool value<unsigned>::parse(const std::string &v, unsigned &res)
{
    return to_number_(v, res);
}
//----------------------------------------------------------------------------
bool value<unsigned long>::parse(const std::string &v, unsigned long &res)
{
    return to_number_(v, res);
}
//----------------------------------------------------------------------------
bool value<unsigned long long>::parse(const std::string &v, unsigned long long &res)
{
    return to_number_(v, res);
}
//----------------------------------------------------------------------------
bool value<bool>::parse(const std::string &v, bool &res)
{
    namespace ascii = __vic::ascii;
    if(v == "1" || ascii::equal_icase(v,"true") || ascii::equal_icase(v,"yes"))
        res = true;
    else if(v == "0" || ascii::equal_icase(v,"false") || ascii::equal_icase(v,"no"))
        res = false;
    else
        return false;
    return true;
}
//----------------------------------------------------------------------------

}} // namespace

#endif // C++11
