//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
void mkdir(const char *path)
{
    if(!::CreateDirectoryA(path, nullptr))
        windows::throw_last_error("CreateDirectory");
}
//----------------------------------------------------------------------------
bool mkdir_if_absent(const char *path)
{
    if(::CreateDirectoryA(path, nullptr)) return true; // Created
    DWORD err = ::GetLastError();
    if(err != ERROR_ALREADY_EXISTS)
        windows::throw_last_error("CreateDirectory", err);
    // Check whether the path is a directory
    if(!dir_exists(path)) windows::throw_last_error("CreateDirectory", err);
    return false; // Path exists and it's a directory
}
//----------------------------------------------------------------------------

} // namespace
