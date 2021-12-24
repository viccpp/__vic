// C++ wrapper for Win32 GDI bitmap
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_WINDOWS_BITMAP_H
#define __VIC_WINDOWS_BITMAP_H

#include<__vic/defs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class Bitmap
{
    HBITMAP hbmp;
public:
    Bitmap() __VIC_DEFAULT_CTR
    explicit Bitmap(HBITMAP h) : hbmp(h) {}

    static Bitmap CreateCompatible(HDC hdc, int w, int h)
        { return Bitmap(::CreateCompatibleBitmap(hdc, w, h)); }

    bool DeleteNT() noexcept { return ::DeleteObject(hbmp); }
    void Delete() { if(!DeleteNT()) throw_failed("DeleteObject"); }

    void ClearHandle() { hbmp = 0; }
    HBITMAP Handle() const { return hbmp; }
    void Handle(HBITMAP h) { hbmp = h; }
    operator HBITMAP() const { return hbmp; }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
