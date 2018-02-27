//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

//----------------------------------------------------------------------------
std::string __vic::get_current_dir()
{
    wchar_t buf[MAX_PATH];
    DWORD n = ::GetCurrentDirectoryW(array_size(buf), buf);
    if(n == 0) windows::throw_last_error("GetCurrentDirectory");
    return windows::utf16to8(buf, n);
}
//----------------------------------------------------------------------------
