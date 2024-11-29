//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
bool copy_file_if_exists(
    const wchar_t *src_path, const wchar_t *dest_path, bool replace)
{
    if(::CopyFileW(src_path, dest_path, !replace)) return true;
    DWORD err = ::GetLastError();
    if(err == ERROR_FILE_NOT_FOUND) return false; // input file doesn't exist
    windows::throw_last_error("CopyFile", err);
}
//----------------------------------------------------------------------------
bool copy_file_if_exists(
    const char *src_path, const char *dest_path, bool replace)
{
    return copy_file_if_exists(
        windows::utf8to16(src_path), windows::utf8to16(dest_path), replace);
}
//----------------------------------------------------------------------------

} // namespace
