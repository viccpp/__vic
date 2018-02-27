//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
void move_file_(const char *src_path, const char *dest_path, DWORD flags)
{
    using windows::utf8to16;
    if(!::MoveFileExW(utf8to16(src_path), utf8to16(dest_path), flags))
        windows::throw_last_error("MoveFileEx");
}
//----------------------------------------------------------------------------

} // namespace
