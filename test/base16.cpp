#include<__vic/base16.h>
#include<__vic/readers/string.h>
#include<__vic/writers/string.h>
#include<iostream>
#include<exception>
#include<cassert>
#include<string>

namespace tests {

typedef std::string bytes;
typedef __vic::string_reader bytes_reader;
typedef __vic::string_writer bytes_writer;

std::string encode_lower(const bytes &s)
{
    std::string res;
    res.reserve(s.length() * 2);
    __vic::base16::encode_lower(bytes_reader(s), __vic::string_writer(res));
    return res;
}
std::string encode_upper(const bytes &s)
{
    std::string res;
    res.reserve(s.length() * 2);
    __vic::base16::encode_upper(bytes_reader(s), __vic::string_writer(res));
    return res;
}
bytes decode(const std::string &s)
{
    bytes res;
    res.reserve(s.length() / 2);
    __vic::base16::decode(__vic::string_reader(s), bytes_writer(res));
    return res;
}
void run()
{
    assert(encode_lower("\x12\x34\xAB") == "1234ab");
    assert(encode_upper("\x12\x34\xAB") == "1234AB");
    assert(decode("1234ab") == "\x12\x34\xAB");
    assert(decode("1234AB") == decode("1234ab"));
    try
    {
        decode("12ZX"); // non-HEX digit
        assert(false);
    }
    catch(const __vic::base16::bad_format & ) {} // OK
    try
    {
        decode("12A"); // odd length
        assert(false);
    }
    catch(const __vic::base16::bad_format & ) {} // OK
}

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
