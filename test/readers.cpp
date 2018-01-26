#include<__vic/readers/container.h>
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
