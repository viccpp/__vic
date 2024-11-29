//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
void rmdir(const wchar_t *path)
{
    if(!::RemoveDirectoryW(path))
        windows::throw_last_error("RemoveDirectory");
}
//----------------------------------------------------------------------------
bool rmdir_if_exists(const wchar_t *path)
{
    if(::RemoveDirectoryW(path)) return true; // removed
    DWORD err = ::GetLastError();
    if(err == ERROR_FILE_NOT_FOUND) return false;
    windows::throw_last_error("RemoveDirectory", err);
}
//----------------------------------------------------------------------------
void rmdir(const char *path)
{
    rmdir(windows::utf8to16(path));
}
//----------------------------------------------------------------------------
bool rmdir_if_exists(const char *path)
{
    return rmdir_if_exists(windows::utf8to16(path));
}
//----------------------------------------------------------------------------

} // namespace
