//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//----------------------------------------------------------------------------
uintmax_t file_size(const wchar_t *path)
{
    WIN32_FILE_ATTRIBUTE_DATA attr;
    if(!::GetFileAttributesExW(path, GetFileExInfoStandard, &attr))
        windows::throw_last_error("GetFileAttributesEx");
    return (uint64_t(attr.nFileSizeHigh) << sizeof(DWORD)) | attr.nFileSizeLow;
}
//----------------------------------------------------------------------------
uintmax_t file_size(const char *path)
{
    return file_size(windows::utf8to16(path));
}
//----------------------------------------------------------------------------

} // namespace
