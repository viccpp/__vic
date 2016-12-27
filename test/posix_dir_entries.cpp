#include<__vic/posix/dir_entries.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<cassert>

namespace tests {

void print(__vic::posix::dir_entries &entries)
{
    while(const char *entry = entries.next())
    {
        assert(entry);
        assert(std::strcmp(entry, ".")  != 0);
        assert(std::strcmp(entry, "..") != 0);
        std::cout << entry << '\n';
    }
}
void run()
{
    __vic::posix::dir_entries all(".");
    assert(all.is_open());
    print(all);
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
