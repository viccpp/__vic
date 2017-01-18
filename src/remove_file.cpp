//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
void remove_file(const char *path)
{
    if(!::DeleteFileA(path)) windows::throw_last_error("DeleteFile");
}
//----------------------------------------------------------------------------
bool remove_file_if_exists(const char *path)
{
    if(::DeleteFileA(path)) return true;
    DWORD err = ::GetLastError();
    if(err == ERROR_FILE_NOT_FOUND) return false;
    windows::throw_last_error("DeleteFile", err);
}
//----------------------------------------------------------------------------
bool remove_file_nt(const char *path) noexcept
{
    return ::DeleteFileA(path);
}
//----------------------------------------------------------------------------

} // namespace
