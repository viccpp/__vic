//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
void move_file_(const wchar_t *src_path, const wchar_t *dest_path, DWORD flags)
{
    if(!::MoveFileExW(src_path, dest_path, flags))
        windows::throw_last_error("MoveFileEx");
}
//----------------------------------------------------------------------------

} // namespace
