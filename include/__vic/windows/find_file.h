// C++ wrapper for Win32 API FindFirstFile()/FindNextFile()
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2019

#ifndef __VIC_WINDOWS_FIND_FILE_H
#define __VIC_WINDOWS_FIND_FILE_H

#include<__vic/defs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class FindFile : public WIN32_FIND_DATA, private non_copyable
{
    HANDLE h;
public:
    FindFile() : h(INVALID_HANDLE_VALUE) {}
    ~FindFile() { if(IsOpen()) ::FindClose(h); }

    bool FindFirst(LPCTSTR );
    bool FindNext();

    bool CloseNT() noexcept
    {
        bool ok = ::FindClose(h);
        h = INVALID_HANDLE_VALUE;
        return ok;
    }
    void Close()
    {
        if(!CloseNT()) throw_last_error("FindClose");
    }
    bool IsOpen() const { return h != INVALID_HANDLE_VALUE; }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
