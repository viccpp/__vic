//
// $Id$
//

#include<__vic/windows/error.h>
#include<windows.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
error::error(DWORD no)
    : code_(no), formatted(false)
{
}
//----------------------------------------------------------------------------
error::error(const char *prompt, DWORD no)
    : code_(no), formatted(false), msg(prompt)
{
}
//----------------------------------------------------------------------------
const char *error::what() const noexcept
{
    try
    {
        if(!formatted)
        {
            const char *err_msg = nullptr;
            DWORD res = ::FormatMessageA(
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_IGNORE_INSERTS |
                FORMAT_MESSAGE_MAX_WIDTH_MASK, // No line breaks
                nullptr,
                code(),
                0,
                reinterpret_cast<LPSTR>(&err_msg),
                0,
                (va_list *) 0
            );
            if(res == 0) err_msg = nullptr;
            class LocalMemKeeper : private non_copyable
            {
                HLOCAL p;
            public:
                explicit LocalMemKeeper(HLOCAL p) : p(p) {}
                // TODO: Use HeapFree() for Windows 10
                ~LocalMemKeeper() { if(p) ::LocalFree(p); }
            } finalizer((HLOCAL) err_msg);
            if(!err_msg) err_msg = "<FormatMessageA() failed>";

            if(msg.empty()) msg = err_msg;
            else
            {
                size_t n = ::lstrlenA(msg) + ::lstrlenA(err_msg) + 3; // 3 is ": " + '\0'
                static_string tmp;
                ::wsprintfA(tmp.reserve(n), "%s: %s",
                                static_cast<const char *>(msg), err_msg);
                msg.swap(tmp);
            }
            formatted = true;
        }
        return msg;
    }
    catch(...)
    {
        return "windows::error::what(): <Couldn't format error message>";
    }
}
//----------------------------------------------------------------------------

}} // namespace
