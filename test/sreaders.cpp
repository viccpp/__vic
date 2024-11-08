#include<__vic/sreaders/defs.h>
#include<__vic/sreaders/container.h>
#include<__vic/sreaders/iterator.h>
#include<__vic/sreaders/string.h>
#include<__vic/sreaders/cstring.h>
#include<__vic/sreaders/cstream.h>
#include<__vic/stdio_file.h>
#include<string>
#include<vector>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

//////////////////////////////////////////////////////////////////////////////
template<class T>
class one_element_reader
{
    int i;
public:
    one_element_reader() : i(1) {}

    __vic::sread_result<T> operator()()
    {
        if(i <= 0) return __vic::sread_eof;
        i--;
        return T();
    }
};
//////////////////////////////////////////////////////////////////////////////

template<class T, class SReader>
void check_read(SReader r)
{
#if __cpp_lib_concepts
    static_assert(__vic::sreader<SReader, T>);
    static_assert(__vic::sreader_result<__vic::sread_result<T>, T>);
#endif
    if(__vic::sread_result<T> res = r())
    {
        T value = res.value();
        (void) value;
    }
#if __cpp_structured_bindings
    auto [value, ok] = r();
    if(ok)
    {
        T check_value_type{value};
        (void) check_value_type;
    }
#endif
}
void container()
{
    std::vector<int> v;
    const int num = 3;
    v.reserve(num);
    for(int i = 1; i <= 3; i++) v.push_back(i);

    __vic::container_sreader<std::vector<int> > r(v);
    for(int i = 1; i <= 3; i++)
    {
        __vic::sread_result<int> n = r();
        assert(n);
        assert(n.value() == i);
    }
    assert(!r());

    check_read<int>(__vic::make_container_sreader(v));
    check_read<unsigned>(__vic::make_container_sreader_for<unsigned>(v));
    check_read<int>(__vic::make_iterator_sreader(v.begin(), v.end()));
    check_read<unsigned>(__vic::make_iterator_sreader_for<unsigned>(v.begin(), v.end()));
    check_read<int>(__vic::make_iterator_sreader_n(v.begin(), v.size()));
    check_read<unsigned>(__vic::make_iterator_sreader_n_for<unsigned>(v.begin(), v.size()));
}
void string()
{
    const char data[] = "abc";
    std::string str(data);

    __vic::string_sreader r(str);
    for(unsigned i = 0; i < str.length(); i++)
    {
        __vic::sread_result<char> ch = r();
        assert(ch);
        assert(ch.value() == data[i]);
    }
    assert(!r());
    check_read<char>(__vic::make_string_sreader(str));
}
void cstring()
{
    const char str[] = "abc";
    __vic::cstring_sreader r(str);
    for(const char *p = str; *p; p++)
    {
        __vic::sread_result<char> ch = r();
        assert(ch);
        assert(ch.value() == *p);
    }
    assert(!r());
    check_read<char>(__vic::make_cstring_sreader(str));
}
void cstream()
{
    __vic::stdio_file file("sreaders.cpp", "r");
    __vic::cstream_sreader r(file);
    __vic::sread_result<char> ch = r();
    assert(ch);
}
template<class ByteType>
void byte_reader_test()
{
    one_element_reader<ByteType> rd;

    if(__VIC_SREAD_RESULT(unsigned char) r = rd())
    {
        unsigned char byte = uchar_value(r);
        (void) byte;
    }
}
void byte_readers()
{
    byte_reader_test<char>();
    byte_reader_test<unsigned char>();
#if __cpp_lib_byte // C++17
    byte_reader_test<std::byte>();
#endif
#if __cpp_char8_t // C++20
    byte_reader_test<char8_t>();
#endif
}
void run()
{
#if __cpp_lambdas
    check_read<int>([]{ return __vic::sread_result<int>(); });
#endif
    container();
    string();
    cstring();
    cstream();
    byte_readers();
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
