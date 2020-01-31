//
// $Id$
//

#include<__vic/windows/error.h>
#include<__vic/ascii.h>
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

            if(err_msg) // trim trailing whitespaces
                while(res && ascii::isspace(err_msg[res-1])) res--;
            else
            {
                static const char stub_msg[] = "<FormatMessageA() failed>";
                err_msg = stub_msg;
                res = sizeof(stub_msg) - 1;
            }

            if(msg.empty()) msg.assign(err_msg, res);
            else
            {
                size_t msg_n = ::lstrlenA(msg);
                readonly_cstring tmp;
                char *p = tmp.reserve(msg_n + res + 3); // 3 is ": " + '\0'
                ::CopyMemory(p, msg, msg_n); p += msg_n;
                *p++ = ':'; *p++ = ' ';
                ::CopyMemory(p, err_msg, res); p += res;
                *p = '\x0';
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
