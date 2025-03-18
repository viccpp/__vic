// Base class for config parsers
//
// Platform: ISO C++ 11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_CONFIG_PARSER_H
#define __VIC_CONFIG_PARSER_H

#include<__vic/config/value.h>
#include<__vic/string_buffer.h>
#include<__vic/error.h>
#include<unordered_map>
#include<memory>
#include<string>

namespace __vic { namespace config {

//////////////////////////////////////////////////////////////////////////////
class parser
{
    class file_source;
    void include(string_buffer & , unsigned );
    abstract_value *find_param(const std::string & ) const;
    void add_param(const char * , std::unique_ptr<abstract_value> );
    static void throw_invalid_format(unsigned );
public:
    struct error : public __vic::exception
    {
        explicit error(const char *msg) : exception(msg) {}
    };
    class source_error : public error
    {
        unsigned line_;
    public:
        source_error(unsigned line, const char *mess) :
            error(__vic::msg(256) << "At line " << line << ": " << mess),
            line_(line) {}
        source_error(const source_error &ex, const char *mess) :
            error(mess), line_(ex.line()) {}
        unsigned line() const { return line_; }
    };
    // attempt to register param twice
    struct duplicate_param : public std::exception
    {
        const char *what() const noexcept;
    };

    parser(const parser & ) = delete;
    parser &operator=(const parser & ) = delete;

    void parse(const char * );
    void parse(const std::string &fname) { parse(fname.c_str()); }
private:
    std::unordered_map<std::string, std::unique_ptr<abstract_value>> params;

    template<class > struct void_ { typedef void type; };
    template<class T, class = void>
    struct value_traits_
    {
        static constexpr bool is_list = false;
        typedef T element_type;
    };
    template<class List> // have list_traits<List> specialization
    struct value_traits_<List, typename void_<
        typename list_traits<List>::value_type>::type>
    {
        static constexpr bool is_list = true;
        typedef typename list_traits<List>::value_type element_type;
    };
    template<class T, class Arg>
    static std::unique_ptr<T> make_unique(Arg &v)
    {
        return std::unique_ptr<T>(new T(v));
    }
protected:
    // No instances (map must be filled in constructor of the derived)
    parser();
    ~parser();

#define __VIC_REGISTER_CONFIG_PARAM(c,p) this->register_param((c).p, #p)
#define __VIC_REGISTER_CONFIG_PARAM_VP(c,p,vp) this->register_param<vp>((c).p, #p)
#define __VIC_REGISTER_COMPLEX_CONFIG_PARAM(c,p,cp) this->register_complex_param<cp>((c).p, #p)
    template<class T>
    void register_param(T &v, const char *name)
    {
        register_param<value<
            typename value_traits_<T>::element_type> >(v, name);
    }
    template<template<class > class ValueParser, class T>
    void register_param(T &v, const char *name)
    {
        register_param<ValueParser<T> >(v, name);
    }
    template<class ValueParser, class T>
    void register_param(T &v, const char *name)
    {
        add_param(name, make_unique<
            atom_value<T, ValueParser, value_traits_<T>::is_list> >(v));
    }
    template<class Parser, class T>
    void register_complex_param(T &v, const char *name)
    {
        add_param(name, make_unique<
            complex_value<T, Parser, value_traits_<T>::is_list> >(v));
    }
};
/////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
