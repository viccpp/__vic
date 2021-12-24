//
// $Id$
//

#include<__vic/windows/shadow_dc.h>
#include<__vic/windows/throw_last_error.h>
#include<cassert>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
ShadowDC::ShadowDC()
{
}
//----------------------------------------------------------------------------
ShadowDC::~ShadowDC()
{
    if(!IsCreated()) return;
    bmp.DeleteNT();
    DeleteNT();
}
//----------------------------------------------------------------------------
void ShadowDC::Create(HWND hwnd)
{
    RECT r;
    if(!::GetClientRect(hwnd, &r)) throw_last_error("GetClientRect");
    assert(r.left == 0 && r.top == 0);

    ClientDC scr_dc(hwnd);
    HDC hdc = ::CreateCompatibleDC(scr_dc);
    if(!hdc) throw_failed("CreateCompatibleDC");
    Handle(hdc);
    bmp = Bitmap::CreateCompatible(scr_dc, r.right, r.bottom);
    if(!bmp) throw_failed("CreateCompatibleBitmap");
    Select(bmp);
}
//----------------------------------------------------------------------------
void ShadowDC::Destroy()
{
    bmp.Delete();
    Delete();
    ClearHandle();
}
//----------------------------------------------------------------------------

}} // namespace
