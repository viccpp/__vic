//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
uintmax_t file_size(const char *path)
{
    using windows::utf8to16;
    WIN32_FILE_ATTRIBUTE_DATA attr;
    if(!::GetFileAttributesExW(utf8to16(path), GetFileExInfoStandard, &attr))
        windows::throw_last_error("GetFileAttributesEx");
    return (uint64_t(attr.nFileSizeHigh) << sizeof(DWORD)) | attr.nFileSizeLow;
}
//----------------------------------------------------------------------------

} // namespace
