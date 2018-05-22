#include<__vic/base64.h>
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

std::string encode(const bytes &s)
{
    std::string res;
    size_t enc_len = __vic::base64::encoded_length(s.length());
    res.reserve(enc_len);
    __vic::base64::encode(bytes_reader(s), __vic::string_writer(res));
    assert(res.length() == enc_len);
    return res;
}
bytes decode(const std::string &s)
{
    bytes res;
    size_t max_dec_len = __vic::base64::max_decoded_length(s.length());
    res.reserve(max_dec_len);
    __vic::base64::decode(__vic::string_reader(s), bytes_writer(res));
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
    catch(const __vic::base64::bad_format & ) {} // OK
    try
    {
        decode("SGVsbG8"); // bad length
        assert(false);
    }
    catch(const __vic::base64::bad_format & ) {} // OK
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
