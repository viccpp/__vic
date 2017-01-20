#include<__vic/base64.h>
#include<iterator>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

typedef std::string bytes;

std::string encode(const bytes &s)
{
    std::string res;
    size_t enc_len = __vic::base64::encoded_length(s.length());
    res.reserve(enc_len);
    __vic::base64::encode(s.begin(), s.end(), std::back_inserter(res));
    assert(res.length() == enc_len);
    return res;
}
bytes decode(const std::string &s)
{
    bytes res;
    size_t max_dec_len = __vic::base64::max_decoded_length(s.length());
    res.reserve(max_dec_len);
    __vic::base64::decode(s.begin(), s.end(), std::back_inserter(res));
    assert(res.length() <= max_dec_len);
    return res;
}
void run()
{
    assert(encode("Hello") == "SGVsbG8=");
    assert(decode("SGVsbG8=") == "Hello");
    try
    {
        decode("!SGVsbG8="); // non-BASE64 digit
        assert(false);
    }
    catch(__vic::base64::bad_format) {} // OK
    try
    {
        decode("SGVsbG8"); // bad length
        assert(false);
    }
    catch(__vic::base64::bad_format) {} // OK
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
