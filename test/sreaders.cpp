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

template<class T, class SReader>
void check_read(SReader r)
{
    T val;
    r.read(val);
    (void) val;
}
void container()
{
    std::vector<int> v;
    const int num = 3;
    v.reserve(num);
    for(int i = 1; i <= 3; i++) v.push_back(i);

    __vic::container_sreader<std::vector<int> > r(v);
    int n;
    for(int i = 1; i <= 3; i++)
    {
        assert(r.read(n));
        assert(n == i);
    }
    assert(!r.read(n));

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
    char ch;
    for(unsigned i = 0; i < str.length(); i++)
    {
        assert(r.read(ch));
        assert(ch == data[i]);
    }
    assert(!r.read(ch));
    check_read<char>(__vic::make_string_sreader(str));
}
void cstring()
{
    const char str[] = "abc";
    __vic::cstring_sreader r(str);
    char ch;
    for(const char *p = str; *p; p++)
    {
        assert(r.read(ch));
        assert(ch == *p);
    }
    assert(!r.read(ch));
    check_read<char>(__vic::make_cstring_sreader(str));
}
void cstream()
{
    __vic::stdio_file file("sreaders.cpp", "r");
    __vic::cstream_sreader r(file);
    char ch;
    r.read(ch);
}
void run()
{
    container();
    string();
    cstring();
    cstream();
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
