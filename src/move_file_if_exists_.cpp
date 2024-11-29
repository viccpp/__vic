//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
bool move_file_if_exists_(
    const wchar_t *src_path, const wchar_t *dest_path, DWORD flags)
{
    if(::MoveFileExW(src_path, dest_path, flags)) return true;
    DWORD err = ::GetLastError();
    if(err == ERROR_FILE_NOT_FOUND) return false; // input file doesn't exist
    windows::throw_last_error("MoveFileEx", err);
}
//----------------------------------------------------------------------------

} // namespace
