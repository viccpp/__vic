#include<__vic/readers/container.h>
#include<__vic/readers/iterator.h>
#include<__vic/readers/string.h>
#include<__vic/readers/cstring.h>
#include<__vic/readers/cstream.h>
#include<__vic/stdio_file.h>
#include<string>
#include<vector>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

template<class T, class Reader>
void check_read(Reader r)
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

    __vic::container_reader<std::vector<int> > r(v);
    int n;
    for(int i = 1; i <= 3; i++)
    {
        assert(r.read(n));
        assert(n == i);
    }
    assert(!r.read(n));

    check_read<int>(__vic::make_container_reader(v));
    check_read<unsigned>(__vic::make_container_reader_for<unsigned>(v));
    check_read<int>(__vic::make_iterator_reader(v.begin(), v.end()));
    check_read<unsigned>(__vic::make_iterator_reader_for<unsigned>(v.begin(), v.end()));
    check_read<int>(__vic::make_iterator_reader_n(v.begin(), v.size()));
    check_read<unsigned>(__vic::make_iterator_reader_n_for<unsigned>(v.begin(), v.size()));
}
void string()
{
    const char data[] = "abc";
    std::string str(data);

    __vic::string_reader r(str);
    char ch;
    for(unsigned i = 0; i < str.length(); i++)
    {
        assert(r.read(ch));
        assert(ch == data[i]);
    }
    assert(!r.read(ch));
    check_read<char>(__vic::make_string_reader(str));
}
void cstring()
{
    const char str[] = "abc";
    __vic::cstring_reader r(str);
    char ch;
    for(const char *p = str; *p; p++)
    {
        assert(r.read(ch));
        assert(ch == *p);
    }
    assert(!r.read(ch));
    check_read<char>(__vic::make_cstring_reader(str));
}
void cstream()
{
    __vic::stdio_file file("readers.cpp", "r");
    __vic::cstream_reader r(file);
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
