//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

//----------------------------------------------------------------------------
bool __vic::copy_file_if_exists(
    const char *src_path, const char *dest_path, bool replace)
{
    using windows::utf8to16;
    if(::CopyFileW(utf8to16(src_path), utf8to16(dest_path), !replace))
        return true;
    DWORD err = ::GetLastError();
    if(err == ERROR_FILE_NOT_FOUND) return false; // input file doesn't exist
    windows::throw_last_error("CopyFile", err);
}
//----------------------------------------------------------------------------
