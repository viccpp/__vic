#include<__vic/windows/window.h>
#include<exception>
#include<windows.h>
#include<cstring>

extern "C" LRESULT CALLBACK WindowFunc(
    HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0); break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
WPARAM window_test(int nWinMode = SW_NORMAL)
{
    using __vic::windows::Window;
    static wchar_t szWinClassName[] = L"TestAppClass";

     Window wnd;
     HINSTANCE hInstance = ::GetModuleHandle(0);
     HICON hIcon = LoadIcon(NULL, IDI_APPLICATION);
     Window::Register(Window::Class(hInstance, szWinClassName, WindowFunc)
        .Icon(hIcon)
        .SmallIcon(hIcon)
        .Cursor(LoadCursor(0, IDC_ARROW))
        .Background((HBRUSH) GetStockObject(GRAY_BRUSH))
    );
    wnd.Create(Window::CreateParams(hInstance, szWinClassName, L"Test"));
    wnd.Show(nWinMode);
    wnd.Update();
    return __vic::windows::MessageLoop();
}
int main(int argc, char *argv[])
{
    try
    {
        if(argc == 2 && std::strcmp(argv[1], "interactive") == 0)
            return window_test();
        return 0;
    }
    catch(const std::exception &ex)
    {
        __vic::windows::MsgBox(ex.what(),
            "Application error", MB_OK | MB_ICONERROR);
    }
    return 1;
}
