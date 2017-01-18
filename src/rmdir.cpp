//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
void rmdir(const char *path)
{
    if(!::RemoveDirectoryA(path)) windows::throw_last_error("RemoveDirectory");
}
//----------------------------------------------------------------------------
bool rmdir_if_exists(const char *path)
{
    if(::RemoveDirectoryA(path)) return true; // removed
    DWORD err = ::GetLastError();
    if(err == ERROR_FILE_NOT_FOUND) return false;
    windows::throw_last_error("RemoveDirectory", err);
}
//----------------------------------------------------------------------------

} // namespace
