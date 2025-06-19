#ifndef __VIC_USE_MODULES
#include<__vic/swriters/defs.h>
#include<__vic/swriters/push_back.h>
#include<__vic/swriters/iterator.h>
#include<__vic/swriters/string.h>
#include<__vic/swriters/cstream.h>
#include<__vic/swriters/null.h>
#include<__vic/stdio_file.h>
#include<vector>
#include<string>
#include<cstdio>
#include<iostream>
#include<exception>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
#include<version>
import std;
import __vic;
#endif

namespace tests {

template<class T, class SWriter>
void check_write(SWriter w, T v)
{
#if __cpp_lib_concepts
    static_assert(__vic::swriter<SWriter, T>);
#endif
    w(v);
}
void push_back()
{
    std::vector<int> v;
    const int num = 3;
    __vic::push_back_swriter<std::vector<int> > w(v);
    for(int i = 0; i < num; i++)
        w(i);
    assert(v.size() == num);
    for(int i = 0; i < num; i++)
        assert(v[i] == i);
    check_write(__vic::make_push_back_swriter(v), 0);
    check_write(__vic::make_push_back_swriter_for<unsigned>(v), 0U);
    check_write(__vic::make_iterator_swriter(v.data()), 0);
    check_write(__vic::make_iterator_swriter_for<unsigned>(v.data()), 0U);
}
void string()
{
    const char data[] = "abc";
    std::string str;
    __vic::string_swriter w(str);
    for(const char *p = data; *p; p++)
        w(*p);
    assert(str == data);
    check_write(__vic::make_string_swriter(str), 'x');
}
void cstream()
{
    const char filename[] = "cstream_swriter.out";
    __vic::stdio_file file(filename, "w");
    __vic::cstream_swriter w(file);
    w('a');
    w('b');
    w('c');
    std::remove(filename);
    check_write(__vic::make_cstream_swriter(file), 'x');
}
void run()
{
#if __cpp_lambdas
    check_write([](int){}, 0);
#endif
    check_write(__vic::make_null_swriter(), 0);
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
