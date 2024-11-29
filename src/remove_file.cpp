//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<exception>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
void remove_file(const wchar_t *path)
{
    if(!::DeleteFileW(path)) windows::throw_last_error("DeleteFile");
}
//----------------------------------------------------------------------------
bool remove_file_if_exists(const wchar_t *path)
{
    if(::DeleteFileW(path)) return true;
    DWORD err = ::GetLastError();
    if(err == ERROR_FILE_NOT_FOUND) return false;
    windows::throw_last_error("DeleteFile", err);
}
//----------------------------------------------------------------------------
bool remove_file_nt(const wchar_t *path) noexcept
{
    return ::DeleteFileW(path);
}
//----------------------------------------------------------------------------
void remove_file(const char *path)
{
    remove_file(windows::utf8to16(path));
}
//----------------------------------------------------------------------------
bool remove_file_if_exists(const char *path)
{
    return remove_file_if_exists(windows::utf8to16(path));
}
//----------------------------------------------------------------------------
bool remove_file_nt(const char *path) noexcept
{
    try {
        return ::DeleteFileW(windows::utf8to16(path));
    } catch(const std::exception &) {
        return false;
    }
}
//----------------------------------------------------------------------------

} // namespace
