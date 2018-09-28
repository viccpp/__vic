#include<__vic/utf16/reader.h>
#include<__vic/utf16/writer.h>
#include<__vic/readers/string.h>
#include<__vic/writers/string.h>
#include<__vic/iterator.h>
#include<string>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

using __vic::unicode_t;
typedef std::basic_string<__vic::utf16::code_unit_t> u16string;

//////////////////////////////////////////////////////////////////////////////
class u16string_code_unit_reader
{
    __vic::basic_string_reader<__vic::utf16::code_unit_t> r;
public:
    explicit u16string_code_unit_reader(const u16string &s) : r(s) {}

    __vic::utf16::status_t read_unit(__vic::utf16::code_unit_t &u)
    {
        if(r.read(u)) return __vic::utf16::status::ok;
        return __vic::utf16::status::eof;
    }
};
//////////////////////////////////////////////////////////////////////////////

#if __cpp_variadic_templates && __cpp_rvalue_references
typedef __vic::utf16::reader<u16string_code_unit_reader> utf16_string_reader;
typedef __vic::utf16::writer<
    __vic::basic_string_writer<__vic::utf16::code_unit_t>
> utf16_string_writer;
#else
struct utf16_string_reader : __vic::utf16::reader<u16string_code_unit_reader>
{
    explicit utf16_string_reader(const u16string &s) :
        __vic::utf16::reader<u16string_code_unit_reader>(
            u16string_code_unit_reader(s)) {}
};
struct utf16_string_writer : __vic::utf16::writer<
    __vic::basic_string_writer<__vic::utf16::code_unit_t> >
{
    explicit utf16_string_writer(u16string &s) :
        __vic::utf16::writer<
            __vic::basic_string_writer<__vic::utf16::code_unit_t>
        >(__vic::basic_string_writer<__vic::utf16::code_unit_t>(s)) {}
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
    for(unicode_t ch; r.read(ch); p++, n--)
    {
        assert(n != 0);
        assert(ch == *p);
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
