#include<__vic/posix/dir_files.h>
#include<cassert>
#include<iostream>
#include<exception>

namespace tests {

void print(__vic::posix::dir_files &files)
{
    while(const char *f = files.next())
        std::cout << f << '\n';
}
void run()
{
    std::cout << "All files:\n";
    __vic::posix::dir_files files(".");
    print(files);

    std::cout << "\n*.cpp files:\n";
    __vic::posix::dir_files cpp_files(".", "*.cpp");
    print(cpp_files);
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
