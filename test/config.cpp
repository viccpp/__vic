#if __cplusplus >= 201103L // C++11

#ifndef __VIC_USE_MODULES
#include<__vic/defs.h>
#include<__vic/config/parser.h>
#include<__vic/config/value.h>
#include<__vic/config/values/std/vector.h>
#include<__vic/config/values/std/list.h>
#include<__vic/config/values/std/forward_list.h>
#include<__vic/config/values/bytes.h>
#include<cstddef>
#include<cstdint>
#include<string>
#include<vector>
#include<list>
#include<sstream>
#include<iostream>
#if __has_include(<optional>)
#include<optional>
#if __cpp_lib_optional
#include<__vic/config/values/std/optional.h>
#endif
#endif
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
#include<version>
#include<__vic/config/parser.macros.h>
import std;
import __vic;
#endif

namespace tests {

//////////////////////////////////////////////////////////////////////////////
struct decoder_instance
{
    std::string msc_vendor;
    std::string file_format;
    std::string folder;
    std::string settings_file;
};
//////////////////////////////////////////////////////////////////////////////
struct complex_param_t
{
    int param1;
    std::vector<std::string> param2;
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

namespace __vic { namespace config {
//////////////////////////////////////////////////////////////////////////////
template<> struct value<tests::decoder_instance>
{
    static bool parse(const std::string &s, tests::decoder_instance &res)
    {
        std::istringstream ss(s);
        ss >> res.msc_vendor >> res.file_format >>
            res.folder >> res.settings_file;
        if(!ss) return false;
        // Make sure that no more that 4 components present
        char ch;
        return !(ss >> ch);
    }
};
//////////////////////////////////////////////////////////////////////////////
}} // namespace

namespace tests {

//////////////////////////////////////////////////////////////////////////////
struct main_config
{
    std::string  str_param;
    std::int32_t int32_param{};
    int          int_param{};
    short        short_param{};
    std::list<std::string>   str_list_param1;
    std::vector<std::string> str_list_param2;
    std::list<decoder_instance> instances;
    bool         bool_param{};
    std::size_t  size_param{};
    unsigned     unsigned_param{};
#if __cpp_lib_optional
    std::optional<unsigned>
#else
    std::string
#endif
        optional_param;
    std::string multiline;
    complex_param_t complex_param;
};
//////////////////////////////////////////////////////////////////////////////
struct main_config_parser : public __vic::config::parser
{
    struct complex_param_parser : public __vic::config::parser
    {
        explicit complex_param_parser(complex_param_t &cfg)
        {
            __VIC_REGISTER_CONFIG_PARAM(cfg, param1);
            __VIC_REGISTER_CONFIG_PARAM(cfg, param2);
        }
    };
    main_config_parser(main_config &cfg)
    {
        __VIC_REGISTER_CONFIG_PARAM(cfg, str_param);
        __VIC_REGISTER_CONFIG_PARAM(cfg, int32_param);
        __VIC_REGISTER_CONFIG_PARAM(cfg, int_param);
        register_param(cfg.short_param, "small_param");
        __VIC_REGISTER_CONFIG_PARAM(cfg, str_list_param1);
        __VIC_REGISTER_CONFIG_PARAM(cfg, str_list_param2);
        register_param(cfg.instances, "cdr_decoders");
        __VIC_REGISTER_CONFIG_PARAM(cfg, bool_param);
        __VIC_REGISTER_CONFIG_PARAM_VP(cfg,
            size_param, __vic::config::bytes_value_parser);
        __VIC_REGISTER_CONFIG_PARAM(cfg, unsigned_param);
        __VIC_REGISTER_CONFIG_PARAM(cfg, optional_param);
        __VIC_REGISTER_CONFIG_PARAM(cfg, multiline);
        __VIC_REGISTER_COMPLEX_CONFIG_PARAM(cfg,
            complex_param, complex_param_parser);
    }
};
//////////////////////////////////////////////////////////////////////////////

#ifndef __VIC_USE_MODULES
#include<iostream>
#endif
//----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const decoder_instance &di)
{
    return os << "( " << di.msc_vendor << ", " << di.file_format << ", " <<
        di.folder << ", " << di.settings_file << " )";
}
//----------------------------------------------------------------------------
template<class TList>
std::ostream &print_list(std::ostream &os, const TList &sl)
{
    os << "{ ";
    for(typename TList::const_iterator it = sl.begin(); it != sl.end(); ++it)
        os << *it << ' ';
    os << '}';
    return os;
}
//----------------------------------------------------------------------------
template<class T>
inline std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    return print_list(os, v);
}
//----------------------------------------------------------------------------
template<class T>
inline std::ostream &operator<<(std::ostream &os, const std::list<T> &l)
{
    return print_list(os, l);
}
//----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &os, const complex_param_t &p)
{
    return os << "( param1: " << p.param1 << ", param2: " << p.param2 << " )";
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void run()
{
    main_config cfg;
    main_config_parser parser(cfg);
    parser.parse("config_sample.cfg");

    std::cout << std::boolalpha <<
        "str_param: " << cfg.str_param << "\n"
        "int32_param: " << cfg.int32_param << "\n"
        "int_param: " << cfg.int_param << "\n"
        "small_param: " << cfg.short_param << "\n"
        "str_list_param1: " << cfg.str_list_param1 << "\n"
        "str_list_param2: " << cfg.str_list_param2 << "\n"
        "cdr_decoders: " << cfg.instances << "\n"
        "bool_param: " << cfg.bool_param << "\n"
        "size_param: " << cfg.size_param << "\n"
        "unsigned_param: " << cfg.unsigned_param << "\n"
        "complex_param " << cfg.complex_param << '\n';

    std::cout << "optional_param: ";
#if __cpp_lib_optional
    if(cfg.optional_param) std::cout << *cfg.optional_param;
#else
    if(!cfg.optional_param.empty()) std::cout << cfg.optional_param;
#endif
    else std::cout << "<NO VALUE>";
    std::cout << "\n";

    std::cout << "multiline: BEGIN\n" << cfg.multiline <<
        "multiline: END\n";
}
//----------------------------------------------------------------------------

} // namespace

#endif // C++11

int main()
{
#if __cplusplus >= 201103L // C++11
    try
    {
        tests::run();
        return 0;
    }
    catch(const __vic::config::parser::error &ex)
    {
        std::cerr << "Config file format error!\n" << ex.what() << '\n';
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
#endif // C++11
}
