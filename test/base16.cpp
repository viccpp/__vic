#include<__vic/base16.h>
#include<iterator>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

typedef std::string bytes;

std::string encode_lower(const bytes &s)
{
    std::string res;
    res.reserve(s.length() * 2);
    __vic::base16::encode_lower(s.begin(), s.end(), std::back_inserter(res));
    return res;
}
std::string encode_upper(const bytes &s)
{
    std::string res;
    res.reserve(s.length() * 2);
    __vic::base16::encode_upper(s.begin(), s.end(), std::back_inserter(res));
    return res;
}
bytes decode(const std::string &s)
{
    bytes res;
    res.reserve(s.length() / 2);
    __vic::base16::decode(s.begin(), s.end(), std::back_inserter(res));
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
    catch(__vic::base16::bad_format) {} // OK
    try
    {
        decode("12A"); // odd length
        assert(false);
    }
    catch(__vic::base16::bad_format) {} // OK
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
