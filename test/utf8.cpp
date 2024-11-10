#include<__vic/utf8/reader.h>
#include<__vic/utf8/writer.h>
#include<__vic/utf8/exceptions.h>
#include<__vic/sreaders/string.h>
#include<__vic/sreaders/cstring.h>
#include<__vic/swriters/string.h>
#include<__vic/iterator.h>
#include<string>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

using __vic::unicode_t;

#if __cpp_variadic_templates && __cpp_rvalue_references
typedef __vic::utf8::reader<__vic::string_sreader> utf8_string_reader;
typedef __vic::utf8::writer<__vic::string_swriter> utf8_string_writer;
typedef __vic::utf8::reader<__vic::cstring_sreader> utf8_cstring_reader;
#else
struct utf8_string_reader : __vic::utf8::reader<__vic::string_sreader>
{
    explicit utf8_string_reader(const std::string &s)
        : __vic::utf8::reader<__vic::string_sreader>(__vic::string_sreader(s)) {}
};
struct utf8_string_writer : __vic::utf8::writer<__vic::string_swriter>
{
    explicit utf8_string_writer(std::string &s)
        : __vic::utf8::writer<__vic::string_swriter>(__vic::string_swriter(s)) {}
};
struct utf8_cstring_reader : __vic::utf8::reader<__vic::cstring_sreader>
{
    explicit utf8_cstring_reader(const char *s)
        : __vic::utf8::reader<__vic::cstring_sreader>(__vic::cstring_sreader(s)) {}
};
#endif

//----------------------------------------------------------------------------
void read_write()
{
    // Unicode code points for u8"Я люблю UTF-8"
    const unicode_t str[] = { 0x042F, 0x20,
        0x043B, 0x044E, 0x0431, 0x043B, 0x044E, 0x20,
        0x55, 0x54, 0x46, 0x2D, 0x38
    };
    // The same string in UTF-8
    const char check[] = "\xD0\xAF" "\x20"
        "\xD0\xBB\xD1\x8E\xD0\xB1\xD0\xBB\xD1\x8E" "\x20"
        "\x55\x54\x46\x2D\x38";

    std::string s;
    utf8_string_writer w(s);
    for(const unicode_t *p = str; p != __vic::end(str); p++)
        w.write(*p);
    assert(s == check);

    utf8_string_reader r(s);
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
void long_code_point()
{
    const unicode_t euro = 0x20AC; // euro sign
    const char euro_utf8[] = "\xE2\x82\xAC";

    utf8_cstring_reader r(euro_utf8);
    __VIC_SREAD_RESULT(unicode_t) ch = r();
    assert(ch);
    assert(ch.value() == euro);
}
//----------------------------------------------------------------------------
template<class UTF8Reader>
bool is_valid(UTF8Reader r)
{
    for(;;)
    {
        __vic::utf8::read_result cp = r.parse();
        switch(cp.status())
        {
            case __vic::utf8::status::ok: break;
            case __vic::utf8::status::eof: return true;
            default: return false;
        }
    }
}
//----------------------------------------------------------------------------
void valid_encoding_test()
{
    const char str[] = "\xD0\xB4""\xD0\xB0""\x20""\x6F""\x6B"; // u8"да ok"
    assert(is_valid(utf8_cstring_reader(str)));
}
//----------------------------------------------------------------------------
template<class UTF8Reader>
__vic::utf8::status_t parse_utf8(UTF8Reader &r)
{
    for(;;)
    {
        __vic::utf8::read_result cp = r.parse();
        switch(cp.status())
        {
            case __vic::utf8::status::ok: break;
            case __vic::utf8::status::eof: return __vic::utf8::status::ok;
            default: return cp.status();
        }
    }
}
//----------------------------------------------------------------------------
size_t offset(const utf8_cstring_reader &r, const char *begin)
{
    return r.get_byte_reader().position() - begin;
}
//----------------------------------------------------------------------------
void code_point_too_big_test()
{
    const char str[] = "\xD0\xB4""\xD0\xB0""\x20""\x6F""\x6B"
        "\xFC\x83\xBF\xBF\xBF\xBF"; // <- 6 bytes length code point
    utf8_cstring_reader r(str);
    assert(parse_utf8(r) == __vic::utf8::status::code_point_too_big);
    assert(offset(r, str) >= 8);
}
//----------------------------------------------------------------------------
void truncated_code_point_test()
{
    const char str[] = "\xD0" // <- truncated code point
        "\xD0\xB0""\x20""\x6F""\x6B";
    utf8_cstring_reader r(str);
    assert(parse_utf8(r) == __vic::utf8::status::truncated_code_point);
    assert(offset(r, str) == 2);
}
//----------------------------------------------------------------------------
void no_leading_byte_test()
{
    const char str[] = "\xD0\xB4""\xB0" // <- continuation byte first
        "\x20""\x6F""\x6B";
    utf8_cstring_reader r(str);
    assert(parse_utf8(r) == __vic::utf8::status::no_leading_byte);
    assert(offset(r, str) == 3);
}
//----------------------------------------------------------------------------
void overlong_encoding_test()
{
    const char str[] = "\xD0\xB4""\xD0\xB0""\x20""\x6F""\x6B"
        "\xF0\x80\x80\xAF"; // <- overlong encoding of U+002F
    utf8_cstring_reader r(str);
    assert(parse_utf8(r) == __vic::utf8::status::overlong_encoding);
    assert(offset(r, str) >= 8);
}
//----------------------------------------------------------------------------
template<class UTF8Reader>
size_t code_point_count(UTF8Reader r)
{
    size_t len = 0;
    while(__VIC_SREAD_RESULT(unicode_t) cp = r()) len++;
    return len;
}
//----------------------------------------------------------------------------
void code_point_count_test()
{
    const char str[] = "\xD0\xB4""\xD0\xB0""\x20""\x6F""\x6B"; // u8"да ok"
    assert(code_point_count(utf8_cstring_reader(str)) == 5);

    const char str_with_nul[] = { 'A', '\0', 'B' };
    assert(code_point_count(utf8_string_reader(
        std::string(str_with_nul, sizeof str_with_nul))) == 3);
}
//----------------------------------------------------------------------------
size_t code_point_length(const char *s)
{
    utf8_cstring_reader r(s);
    if(__VIC_SREAD_RESULT(unicode_t) cp = r())
        return offset(r, s);
    return 0;
}
//----------------------------------------------------------------------------
void code_point_length_test()
{
    const char ch1[] = ".",
        ch2[] = "\xD0\x90",     // UTF-8: А
        ch3[] = "\xE2\x82\xAC", // euro sign
        ch4[] = "\xF0";         // First byte of the 4-byte-length char

    assert(code_point_length(ch1) == 1);
    assert(code_point_length(ch2) == 2);
    assert(code_point_length(ch3) == 3);
    try
    {
        code_point_length(ch4);
        assert(false);
    }
    catch(const __vic::utf8::truncated_code_point & ) {} // OK
    catch(...) { assert(false); }
}
//----------------------------------------------------------------------------
std::string replace_invalid(const char *str, unicode_t ch)
{
    utf8_cstring_reader r(str);
    std::string res;
    bool skip_continuation_bytes = false;
    for(;;)
    {
        const char *begin = r.get_byte_reader().position();
        __vic::utf8::read_result cp = r.parse();
        switch(cp.status())
        {
            case __vic::utf8::status::ok:
                res.append(begin, r.get_byte_reader().position() - begin);
                skip_continuation_bytes = false;
                break;
            case __vic::utf8::status::eof:
                return res;
            case __vic::utf8::status::no_leading_byte:
                if(skip_continuation_bytes) break;
                // [[fallthrough]];
            default:
                utf8_string_writer(res).write(ch);
                skip_continuation_bytes = true;
        }
    }
}
//----------------------------------------------------------------------------
void replace_invalid_test()
{
    // The first is a Euro sign w/o leading byte
    const char str[] = /*"\xE2"*/"\x82\xAC""xz";
    assert(!is_valid(utf8_cstring_reader(str)));
    std::string fixed = replace_invalid(str, '?');
    std::cout << fixed << '\n';
    assert(fixed == "?xz");
    assert(is_valid(utf8_string_reader(fixed)));
}
//----------------------------------------------------------------------------
void run()
{
    read_write();
    long_code_point();
    valid_encoding_test();
    code_point_too_big_test();
    truncated_code_point_test();
    no_leading_byte_test();
    overlong_encoding_test();
    code_point_count_test();
    code_point_length_test();
    replace_invalid_test();
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
