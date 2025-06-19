#ifndef __VIC_USE_MODULES
#include<__vic/utf16/reader.h>
#include<__vic/utf16/writer.h>
#include<__vic/sreaders/string.h>
#include<__vic/swriters/string.h>
#include<__vic/iterator.h>
#include<string>
#include<iostream>
#include<exception>
#include<cstddef>
#include<cstring>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#define __VIC_SREAD_RESULT(T) auto
#endif

namespace tests {

using __vic::unicode_t;
using std::size_t;
#if __cpp_unicode_characters
using std::u16string;
#else
// std::char_traits<uint_least16_t> may not be supported
struct utf16_char_traits
{
    typedef __vic::utf16::code_unit_t char_type;
    typedef __vic::utf16::code_unit_t int_type;
    typedef std::streamoff off_type;
    typedef std::wstreampos pos_type;
    typedef std::mbstate_t state_type;

    static void assign(char_type &c1, const char_type &c2) { c1 = c2; }
    static bool eq(char_type c1, char_type c2) { return c1 == c2; }
    static bool lt(char_type c1, char_type c2) { return c1 < c2; }

    static int compare(const char_type *s1, const char_type *s2, std::size_t n)
    {
        return std::memcmp(s1, s2, n * sizeof(char_type));
    }
    static std::size_t length(const char_type *s)
    {
        std::size_t n = 0;
        for(; *s; s++) n++;
        return n;
    }
    static const char_type *find(
        const char_type *s, std::size_t n, const char_type &a)
    {
        for(; n; n--, s++)
            if(*s == a) return s;
        return 0;
    }
    static char_type *move(char_type *s1, const char_type *s2, std::size_t n)
    {
        std::memmove(s1, s2, n * sizeof(char_type));
        return s1;
    }
    static char_type *copy(char_type *s1, const char_type *s2, std::size_t n)
    {
        std::memcpy(s1, s2, n * sizeof(char_type));
        return s1;
    }
    static char_type *assign(char_type *s, std::size_t n, char_type a)
    {
        for(char_type *p = s; n; n--) *p++ = a;
        return s;
    }

    static int_type not_eof(int_type c) { return c != eof() ? c : 0; }
    static char_type to_char_type(int_type c) { return c; }
    static int_type to_int_type(char_type c) { return c; }
    static bool eq_int_type(int_type c1, int_type c2) { return c1 == c2; }
    static int_type eof() { return static_cast<int_type>(-1); }
};
typedef std::basic_string<__vic::utf16::code_unit_t,
                          utf16_char_traits> u16string;
#endif

//////////////////////////////////////////////////////////////////////////////
class u16string_code_unit_reader
{
    __vic::basic_string_sreader<__vic::utf16::code_unit_t> r;
public:
    explicit u16string_code_unit_reader(const u16string &s) : r(s) {}

    __vic::utf16::read_unit_result operator()()
    {
        if(__vic::sread_result<__vic::utf16::code_unit_t> u = r())
            return u.value();
        return __vic::utf16::status::eof;
    }
};
//////////////////////////////////////////////////////////////////////////////

#if __cpp_variadic_templates && __cpp_rvalue_references
typedef __vic::utf16::reader<u16string_code_unit_reader> utf16_string_reader;
typedef __vic::utf16::writer<
    __vic::push_back_swriter<u16string>
> utf16_string_writer;
#else
struct utf16_string_reader : __vic::utf16::reader<u16string_code_unit_reader>
{
    explicit utf16_string_reader(const u16string &s) :
        __vic::utf16::reader<u16string_code_unit_reader>(
            u16string_code_unit_reader(s)) {}
};
struct utf16_string_writer :
    __vic::utf16::writer<__vic::push_back_swriter<u16string> >
{
    explicit utf16_string_writer(u16string &s) :
        __vic::utf16::writer<__vic::push_back_swriter<u16string> >(
            __vic::push_back_swriter<u16string>(s)) {}
};
#endif

//----------------------------------------------------------------------------
void read_write()
{
    // Unicode code points for u8"Я ненавижу UTF-16"
    const unicode_t str[] = { 0x042F, 0x20,
        0x043D, 0x0435, 0x043D, 0x0430, 0x0432, 0x0438, 0x0436, 0x0443, 0x20,
        0x55, 0x54, 0x46, 0x2D, 0x31, 0x36
    };
    // The same string in UTF-16LE
    const __vic::utf16::code_unit_t check[] = { 0x042F,  0x20,
        0x043D, 0x0435, 0x043D, 0x0430, 0x0432, 0x0438, 0x0436, 0x0443,
        0x20,  0x55, 0x54, 0x46, 0x2D, 0x31, 0x36,  0 };

    u16string s;
    utf16_string_writer w(s);
    for(const unicode_t *p = str; p != __vic::end(str); p++)
        w.write(*p);
    assert(s == check);

    utf16_string_reader r(s);
    const unicode_t *p = str;
    size_t n = __vic::array_size(str);
    for(; __VIC_SREAD_RESULT(unicode_t) ch = r(); p++, n--)
    {
        assert(n != 0);
        assert(ch.value() == *p);
    }
    assert(n == 0); // all str elements are read
}
//----------------------------------------------------------------------------
void run()
{
    read_write();
}
//----------------------------------------------------------------------------

} // namespace

int main()
{
    try
    {
        tests::run();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
