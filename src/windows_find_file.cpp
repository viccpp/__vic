//
// $Id$
//

#include<__vic/windows/find_file.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
// True for "." and ".." entries
inline bool is_special(LPCTSTR f)
{
    return *f == TEXT('.') &&
        (f[1] == TEXT('\0') || (f[1] == TEXT('.') && f[2] == TEXT('\0')));
}
//----------------------------------------------------------------------------
bool FindFile::FindFirst(LPCTSTR filename)
{
    h = ::FindFirstFile(filename, this);
    if(IsOpen())
    {
        if(is_special(this->cFileName)) return FindNext();
        return true;
    }
    DWORD err = ::GetLastError();
    if(err != ERROR_FILE_NOT_FOUND)
        throw_last_error("FindFirstFile", err);
    return false;
}
//----------------------------------------------------------------------------
bool FindFile::FindNext()
{
    for(;;)
    {
        if(::FindNextFile(h, this))
        {
            if(is_special(this->cFileName)) continue;
            return true;
        }
        DWORD err = ::GetLastError();
        if(err != ERROR_NO_MORE_FILES)
            throw_last_error("FindNextFile", err);
        return false;
    }
}
//----------------------------------------------------------------------------

}} // namespace
