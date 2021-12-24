// Virtual in-memory DC
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_WINDOWS_SHADOW_DC_H
#define __VIC_WINDOWS_SHADOW_DC_H

#include<__vic/defs.h>
#include<__vic/windows/dc.h>
#include<__vic/windows/bitmap.h>

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class ShadowDC : public DC, private non_copyable
{
    Bitmap bmp;
public:
    ShadowDC();
    ~ShadowDC();

    void Create(HWND );
    void Destroy();
    bool IsCreated() const { return Handle(); }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
