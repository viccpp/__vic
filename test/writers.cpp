#include<__vic/writers/push_back.h>
#include<__vic/writers/string.h>
#include<__vic/writers/cstream.h>
#include<__vic/stdio_file.h>
#include<vector>
#include<string>
#include<cstdio>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

void push_back()
{
    std::vector<int> v;
    const int num = 3;
    __vic::push_back_writer<std::vector<int> > w(v);
    for(int i = 0; i < num; i++)
        w.write(i);
    assert(v.size() == num);
    for(int i = 0; i < num; i++)
        assert(v[i] == i);
}
void string()
{
    const char data[] = "abc";
    std::string str;
    __vic::string_writer w(str);
    for(const char *p = data; *p; p++)
        w.write(*p);
    assert(str == data);
}
void cstream()
{
    const char filename[] = "cstream_writer.out";
    __vic::stdio_file file(filename, "w");
    __vic::cstream_writer w(file);
    w.write('a');
    w.write('b');
    w.write('c');
    std::remove(filename);
}
void run()
{
    push_back();
    string();
    //cstream();
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
