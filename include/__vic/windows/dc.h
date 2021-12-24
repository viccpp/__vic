// C++ wrapper for Win32 GDI device context (DC)
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_WINDOWS_DC_H
#define __VIC_WINDOWS_DC_H

#include<__vic/defs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class DC
{
    HDC hdc;
public:
    DC() __VIC_DEFAULT_CTR
    explicit DC(HDC hdc) : hdc(hdc) {}

    static DC CreateCompatible(HDC hdc) { return DC(::CreateCompatibleDC(hdc)); }

    bool ReleaseNT(HWND hwnd) noexcept { return ::ReleaseDC(hwnd, hdc); }
    void Release(HWND hwnd) { if(!ReleaseNT(hwnd)) throw_failed("ReleaseDC"); }
    bool DeleteNT() noexcept { return ::DeleteDC(hdc); }
    void Delete() { if(!DeleteNT()) throw_failed("DeleteDC"); }

    int GetHorzRes() const { return ::GetDeviceCaps(hdc, HORZRES); }
    int GetVertRes() const { return ::GetDeviceCaps(hdc, VERTRES); }
    HWND GetWindow() const { return ::WindowFromDC(hdc); }
    HGDIOBJ GetCurrentObject(UINT uObjType) const { return ::GetCurrentObject(hdc, uObjType); }
    HBRUSH GetCurrentBrush() const { return (HBRUSH) GetCurrentObject(OBJ_BRUSH); }
    HPEN GetCurrentPen() const { return (HPEN) GetCurrentObject(OBJ_PEN); }
    HFONT GetCurrentFont() const { return (HFONT) GetCurrentObject(OBJ_FONT); }
    HBITMAP GetCurrentBitmap() const { return (HBITMAP) GetCurrentObject(OBJ_BITMAP); }

    void Select(HGDIOBJ hObj) // not a region object
        { if(!::SelectObject(hdc, hObj)) throw_failed("SelectObject"); }
    void Select(HRGN hReg)
        { if(::SelectObject(hdc, hReg) == HGDI_ERROR) throw_failed("SelectObject"); }

    COLORREF SetPixel(int x, int y, COLORREF c) { return ::SetPixel(hdc, x, y, c); }
    bool MoveTo(int x, int y, POINT *p = 0) { return ::MoveToEx(hdc, x, y, p); }
    bool LineTo(int x, int y) { return ::LineTo(hdc, x, y); }
    bool PolyBezier(const POINT *lppt, DWORD cPoints) { return ::PolyBezier(hdc, lppt, cPoints); }
    bool FillRect(const RECT &rect, HBRUSH hbr) { return ::FillRect(hdc, &rect, hbr); }

    bool BlitTo(HDC dcDest, int x, int y, int w, int h, DWORD dwRop = SRCCOPY) const
    {
        return ::BitBlt(dcDest, x, y, w, h, hdc, x, y, dwRop);
    }
    bool BlitTo(HDC dcDest, const RECT &r, DWORD dwRop = SRCCOPY) const
    {
        return ::BitBlt(dcDest, r.left, r.top,
            r.right - r.left, r.bottom - r.top, hdc, r.left, r.top, dwRop);
    }

    void ClearHandle() { hdc = 0; }
    HDC Handle() const { return hdc; }
    void Handle(HDC hDc) { hdc = hDc; }
    operator HDC() const { return hdc; }
};
//////////////////////////////////////////////////////////////////////////////
class ClientDC : public DC, private non_copyable
{
    HWND hwnd;
public:
    explicit ClientDC(HWND hwnd) : DC(::GetDC(hwnd)), hwnd(hwnd)
        { if(!Handle()) throw_failed("GetDC"); }
    ClientDC(HDC hdc, HWND hwnd) : DC(hdc), hwnd(hwnd) {}
    ~ClientDC() { ReleaseNT(hwnd); }
};
//////////////////////////////////////////////////////////////////////////////
class PaintDC : public DC, public PAINTSTRUCT, private non_copyable
{
    HWND hwnd;
public:
    explicit PaintDC(HWND hwnd) : DC(::BeginPaint(hwnd, this)), hwnd(hwnd)
        { if(!Handle()) throw_failed("BeginPaint"); }
    ~PaintDC() { ::EndPaint(hwnd, this); }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
