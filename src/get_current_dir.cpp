//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

//----------------------------------------------------------------------------
std::string __vic::get_current_dir()
{
    char buf[MAX_PATH];
    if(::GetCurrentDirectoryA(sizeof buf, buf) == 0)
        windows::throw_last_error("GetCurrentDirectory");
    return buf;
}
//----------------------------------------------------------------------------
