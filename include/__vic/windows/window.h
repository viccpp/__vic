// Thin C++ wrapper for HWND
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_WINDOWS_WINDOW_H
#define __VIC_WINDOWS_WINDOW_H

#include<__vic/defs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class Window
{
    HWND hwnd;
public:
    struct Class;
    struct CreateParams;

    Window() __VIC_DEFAULT_CTR
    explicit Window(HWND h) : hwnd(h) {}

    static void Register(WNDCLASSEXW wcl)
    {
        if(!::RegisterClassExW(&wcl)) throw_last_error("RegisterClassExW");
    }
    void Create(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWndName,
        DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent,
        HMENU hMenu, HINSTANCE hInstance, void *lpParam = nullptr)
    {
        HWND h = ::CreateWindowExW(dwExStyle, lpClassName, lpWndName, dwStyle,
                    x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
        if(!h) throw_last_error("CreateWindowExW");
        hwnd = h;
    }
    void Create(const CREATESTRUCTW &cs)
    {
        Create(cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y,
            cs.cx, cs.cy, cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);
    }

    LRESULT SendMessage(UINT msg, WPARAM w = 0, LPARAM l = 0)
        { return ::SendMessage(hwnd, msg, w, l); }

    void Update() { if(!::UpdateWindow(hwnd)) throw_failed("UpdateWindow"); }
    bool Show(int nWinMode) { return ::ShowWindow(hwnd, nWinMode); }
    void Redraw(const RECT *rect = 0, HRGN hrgn = 0,
                        UINT flags = RDW_INVALIDATE | RDW_UPDATENOW) //| RDW_ERASE
    {
        if(!::RedrawWindow(hwnd, rect, hrgn, flags))
            throw_failed("RedrawWindow");
    }

    void GetRect(RECT &r) const
        { if(!::GetWindowRect(hwnd, &r)) throw_last_error("GetWindowRect"); }
    RECT GetRect() const { RECT r; GetRect(r); return r; }
    void GetClientRect(RECT &r) const
        { if(!::GetClientRect(hwnd, &r)) throw_last_error("GetClientRect"); }
    RECT GetClientRect() const { RECT r; GetClientRect(r); return r; }

    void SetText(LPCWSTR st)
    {
        if(!::SetWindowTextW(hwnd, st)) throw_last_error("SetWindowTextW");
    }
    void SetText(const char * );
    int GetText(LPWSTR st, int nMax) const { return ::GetWindowTextW(hwnd, st, nMax); }

    void SetPos(HWND hWndAfter, int x, int y, int w, int h, UINT uFlags)
    {
        if(!::SetWindowPos(hwnd, hWndAfter, x, y, w, h, uFlags))
            throw_last_error("SetWindowPos");
    }
    void SetPos(int x, int y, int w, int h) { SetPos(0, x, y, w, h, SWP_NOZORDER); }
    void SetSize(int w, int h) { SetPos(0, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE); }
    void SetClientAreaSize(int , int );
    void MoveTo(int x, int y) { SetPos(0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE); }
    void MoveToCenter();

    HWND Handle() const { return hwnd; }
    void Handle(HWND h) { hwnd = h; }
    operator HWND() const { return hwnd; }
};
//////////////////////////////////////////////////////////////////////////////
struct Window::Class : WNDCLASSEXW
{
    Class(HMODULE hInst, LPCWSTR name, WNDPROC wndProc)
    {
        cbSize = sizeof(WNDCLASSEXW);
        style = 0;
        lpfnWndProc = wndProc;
        cbClsExtra = cbWndExtra = 0;
        hInstance = hInst;
        hIcon = 0;
        hCursor = ::LoadCursorW(0, IDC_ARROW);
        hbrBackground = 0;
        lpszMenuName = 0;
        lpszClassName = name;
        hIconSm = 0;
    }
    Class &Style(UINT v) { style = v; return *this; }
    Class &ClsExtra(int v) { cbClsExtra = v; return *this; }
    Class &WndExtra(int v) { cbWndExtra = v; return *this; }
    Class &Instance(HINSTANCE v) { hInstance = v; return *this; }
    Class &Icon(HICON v) { hIcon = v; return *this; }
    Class &Cursor(HCURSOR v) { hCursor = v; return *this; }
    Class &Background(HBRUSH v) { hbrBackground = v; return *this; }
    Class &MenuName(LPCWSTR v) { lpszMenuName = v; return *this; }
    Class &SmallIcon(HICON v) { hIconSm = v; return *this; }
};
//////////////////////////////////////////////////////////////////////////////
struct Window::CreateParams : CREATESTRUCTW
{
    CreateParams(HMODULE hInst, LPCWSTR lpClsName, LPCWSTR lpWndName = nullptr)
    {
        lpCreateParams = 0;
        hInstance = hInst;
        hMenu = 0;
        hwndParent = HWND_DESKTOP;
        cy = cx = y = x = CW_USEDEFAULT;
        style = WS_OVERLAPPEDWINDOW;
        lpszName = lpWndName;
        lpszClass = lpClsName;
        dwExStyle = 0;
    }
    CreateParams &ExtraParam(void *v) { lpCreateParams = v; return *this; }
    CreateParams &Instance(HINSTANCE v) { hInstance = v; return *this; }
    CreateParams &Menu(HMENU v) { hMenu = v; return *this; }
    CreateParams &Parent(HWND v) { hwndParent = v; return *this; }
    CreateParams &Position(int X, int Y) { x = X; y = Y; return *this; }
    CreateParams &Dimension(int w, int h) { cx = w; cy = h; return *this; }
    CreateParams &Style(DWORD v) { style = v; return *this; }
    CreateParams &ExStyle(DWORD v) { dwExStyle = v; return *this; }
};
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline int MsgBox(HWND hwnd, LPCWSTR msg, LPCWSTR title = L"", int t = MB_OK)
    { return ::MessageBoxW(hwnd, msg, title, t); }
inline int MsgBox(LPCWSTR msg, LPCWSTR title = L"", int t = MB_OK)
    { return MsgBox(0, msg, title, t); }
int MsgBox(HWND , const char * , const char * = "", int = MB_OK);
inline int MsgBox(const char *msg, const char *title = "", int t = MB_OK)
    { return MsgBox(0, msg, title, t); }
//----------------------------------------------------------------------------

WPARAM MessageLoop(HWND = NULL);
bool ProcessMessages(HWND = NULL);

}} // namespace

#endif // header guard
