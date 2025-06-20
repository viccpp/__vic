#ifndef __VIC_USE_MODULES
#include<__vic/windows/find_file.h>
#include<__vic/windows/wchar.h>
#include<iostream>
#include<exception>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
#include<__vic/modules/windows.h>
import std;
import __vic;
#endif

namespace tests {

void list(LPCTSTR path)
{
    __vic::windows::FindFile ff;
    if(!ff.FindFirst(path)) return;
    do {
        std::cout <<
#ifdef UNICODE
            __vic::windows::utf16to8
#endif
            (ff.cFileName) << '\n';
    } while(ff.FindNext());
}
void run()
{
    std::cout << "All files:\n";
    list(TEXT(".\\*"));

    std::cout << "\n*.cpp files:\n";
    list(TEXT(".\\*.cpp"));
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
