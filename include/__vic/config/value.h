// Config parameter value parsers
//
// Platform: ISO C++ 11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_CONFIG_VALUE_H
#define __VIC_CONFIG_VALUE_H

#include<__vic/string_buffer.h>
#include<string>

namespace __vic { namespace config {

// Not defined. Shall be specialized to use
template<class List> struct list_traits;
//{
//    typename value_type;
//    static void push(List &c, value_type &&v);
//};

class parser; // forward
//////////////////////////////////////////////////////////////////////////////
class source
{
public:
    virtual void read(parser & ) = 0;
};
//////////////////////////////////////////////////////////////////////////////
class abstract_value
{
public:
    virtual ~abstract_value() = default;
    virtual bool parse(const std::string & ) = 0;
    virtual void parse(source & ) = 0;
    virtual bool is_complex() const = 0;
    virtual bool is_list() const;
};
//////////////////////////////////////////////////////////////////////////////
struct abstract_atom_value : public abstract_value
{
    using abstract_value::parse;
    void parse(source & ) final;
    bool is_complex() const final;
};
//////////////////////////////////////////////////////////////////////////////
struct abstract_complex_value : public abstract_value
{
    using abstract_value::parse;
    bool parse(const std::string & ) final;
    bool is_complex() const final;
};
//////////////////////////////////////////////////////////////////////////////
struct abstract_atom_list_value : public abstract_atom_value
{
    bool is_list() const final;
};
//////////////////////////////////////////////////////////////////////////////
struct abstract_complex_list_value : public abstract_complex_value
{
    bool is_list() const final;
};
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
template<class Value, class ValueParser, bool IsList = false>
class atom_value : public abstract_atom_value
{
    Value *pValue;
public:
    explicit atom_value(Value &v) : pValue(&v) {}
    using abstract_atom_value::parse;
    bool parse(const std::string & ) final;
};
//////////////////////////////////////////////////////////////////////////////
template<class List, class ValueParser>
class atom_value<List,ValueParser,true> : public abstract_atom_list_value
{
    List *pList;
public:
    explicit atom_value(List &v) : pList(&v) {}
    using abstract_atom_list_value::parse;
    bool parse(const std::string & ) final;
};
//////////////////////////////////////////////////////////////////////////////
template<class Value, class Parser, bool IsList = false>
class complex_value : public abstract_complex_value
{
    Value *pValue;
public:
    explicit complex_value(Value &v) : pValue(&v) {}
    using abstract_complex_value::parse;
    void parse(source & ) final;
};
//////////////////////////////////////////////////////////////////////////////
template<class List, class Parser>
class complex_value<List,Parser,true> : public abstract_complex_list_value
{
    List *pList;
public:
    explicit complex_value(List &v) : pList(&v) {}
    using abstract_complex_list_value::parse;
    void parse(source & ) final;
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class T, class ValueParser, bool IsList>
bool atom_value<T,ValueParser,IsList>::parse(const std::string &s)
{
    return ValueParser::parse(s, *pValue);
}
//----------------------------------------------------------------------------
template<class List, class ValueParser>
bool atom_value<List,ValueParser,true>::parse(const std::string &s)
{
    typedef typename list_traits<List>::value_type element_type;
    element_type v;
    if(!ValueParser::parse(s, v)) return false;
    list_traits<List>::push(*pList, std::move(v));
    return true;
}
//----------------------------------------------------------------------------
template<class Value, class Parser, bool IsList>
void complex_value<Value,Parser,IsList>::parse(source &s)
{
    Parser p(*pValue);
    s.read(p);
}
//----------------------------------------------------------------------------
template<class List, class Parser>
void complex_value<List,Parser,true>::parse(source &s)
{
    typedef typename list_traits<List>::value_type element_type;
    element_type v{};
    complex_value<element_type,Parser>(v).parse(s);
    list_traits<List>::push(*pList, std::move(v));
}
//----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
// Not defined. Shall be specialized to use
template<class > class value;
//////////////////////////////////////////////////////////////////////////////
// Predefined config value parsers
//////////////////////////////////////////////////////////////////////////////
template<> struct value<std::string>
{
    static bool parse(const std::string &s, std::string &res)
    {
        res = s;
        return true;
    }
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<string_buffer>
{
    static bool parse(const std::string &s, string_buffer &res)
    {
        res = s;
        return true;
    }
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<signed char>
{
    static bool parse(const std::string & , signed char & );
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<short>
{
    static bool parse(const std::string & , short & );
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<int>
{
    static bool parse(const std::string & , int & );
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<long>
{
    static bool parse(const std::string & , long & );
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<long long>
{
    static bool parse(const std::string & , long long & );
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<unsigned char>
{
    static bool parse(const std::string & , unsigned char & );
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<unsigned short>
{
    static bool parse(const std::string & , unsigned short & );
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<unsigned>
{
    static bool parse(const std::string & , unsigned & );
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<unsigned long>
{
    static bool parse(const std::string & , unsigned long & );
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<unsigned long long>
{
    static bool parse(const std::string & , unsigned long long & );
};
//////////////////////////////////////////////////////////////////////////////
template<> struct value<bool>
{
    static bool parse(const std::string & , bool & );
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
