#include<__vic/base64.h>
#include<__vic/sreaders/string.h>
#include<__vic/swriters/string.h>
#include<__vic/ascii.h>
#include<iostream>
#include<exception>
#include<cstddef>
#include<cassert>
#include<string>

namespace tests {

typedef std::string bytes;
typedef __vic::string_sreader bytes_sreader;
typedef __vic::string_swriter bytes_swriter;
template<class SReader>
class skip_ws_sreader
{
    SReader r;
public:
    template<class Arg>
    explicit skip_ws_sreader(Arg &arg) : r(arg) {}
    __vic::sread_result<char> operator()()
    {
        for(;;)
        {
            __vic::sread_result<char> ch = r();
            if(!ch) return __vic::sread_eof;
            if(__vic::ascii::isspace(ch.value())) continue;
            return ch.value();
        }
    }
};

std::string encode(const bytes &s)
{
    std::string res;
    std::size_t enc_len = __vic::base64::encoded_length(s.length());
    res.reserve(enc_len);
    __vic::base64::encode(bytes_sreader(s), __vic::string_swriter(res));
    assert(res.length() == enc_len);
    return res;
}
bytes decode(const std::string &s)
{
    bytes res;
    std::size_t max_dec_len = __vic::base64::max_decoded_length(s.length());
    res.reserve(max_dec_len);
    __vic::base64::decode(__vic::string_sreader(s), bytes_swriter(res));
    assert(res.length() <= max_dec_len);
    return res;
}
bytes decode_ignore_ws(const std::string &s)
{
    bytes res;
    std::size_t max_dec_len = __vic::base64::max_decoded_length(s.length());
    res.reserve(max_dec_len);
    __vic::base64::decode(
        skip_ws_sreader<__vic::string_sreader>(s), bytes_swriter(res));
    assert(res.length() <= max_dec_len);
    return res;
}
void run()
{
    assert(encode("Hello") == "SGVsbG8=");
    assert(decode("SGVsbG8=") == "Hello");
    assert(decode_ignore_ws(" S G Vs bG8 = ") == "Hello");
    try
    {
        decode("!SGVsbG8="); // non-BASE64 digit
        assert(false);
    }
    catch(const __vic::base64::bad_digit & ) {} // OK
    try
    {
        decode("SGVsbG8"); // bad length
        assert(false);
    }
    catch(const __vic::base64::bad_length & ) {} // OK
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
