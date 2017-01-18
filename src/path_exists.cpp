//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/string_buffer.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

namespace {
//----------------------------------------------------------------------------
bool get_file_attr(const char *path, DWORD &attr, const char *what)
{
    // TODO: the call doesn't follow symbolic links as opposed to POSIX stat()
    // FILE_ATTRIBUTE_REPARSE_POINT is set for symlink
    attr = ::GetFileAttributesA(path);
    if(attr != INVALID_FILE_ATTRIBUTES) return true;
    DWORD err = ::GetLastError();
    switch(err)
    {
        case ERROR_FILE_NOT_FOUND:
            return false;
    }
    windows::throw_last_error(__vic::msg(256) <<
        "Can't get attributes of " << what << " \"" << path << '"');
}
//----------------------------------------------------------------------------
} // namespace
//----------------------------------------------------------------------------
bool path_exists(const char *path)
{
#if 0
    return ::PathFileExistsA(path); // depends on Shlwapi.dll
#else
    DWORD attr;
    return get_file_attr(path,attr,"path");
#endif
}
//----------------------------------------------------------------------------
bool file_exists(const char *path)
{
    DWORD attr;
    // TODO: no special attribute to distinguish regular file
    // so using elimination approach
    return get_file_attr(path,attr,"file") &&
        !(attr & FILE_ATTRIBUTE_DIRECTORY);
}
//----------------------------------------------------------------------------
bool dir_exists(const char *path)
{
    DWORD attr;
    return get_file_attr(path,attr,"dir") && (attr & FILE_ATTRIBUTE_DIRECTORY);
}
//----------------------------------------------------------------------------

} // namespace
