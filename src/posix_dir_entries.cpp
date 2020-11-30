//
// $Id$
//

#include<__vic/posix/dir_entries.h>
#include<__vic/throw_errno.h>
#include<__vic/string_buffer.h>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
// True for "." and ".." entries
inline bool dir_entries::is_special(const char *f)
{
    return *f == '.' && (f[1] == '\0' || (f[1] == '.' && f[2] == '\0'));
}
//----------------------------------------------------------------------------
dir_entries::dir_entries(const char *path)
    : dir(::opendir(path))
{
}
//----------------------------------------------------------------------------
dir_entries::~dir_entries()
{
    if(is_open()) ::closedir(dir);
}
//----------------------------------------------------------------------------
#if __cpp_rvalue_references
dir_entries &dir_entries::operator=(dir_entries &&o) noexcept
{
    std::swap(dir, o.dir);
    entry = std::move(o.entry);
    return *this;
}
#endif
//----------------------------------------------------------------------------
bool dir_entries::reopen(const char *path)
{
    if(is_open()) close();
    DIR *d = ::opendir(path);
    if(!d) return false;
    dir = d;
    return true;
}
//----------------------------------------------------------------------------
void dir_entries::close()
{
    if(::closedir(dir)) throw_errno("closedir");
    dir = nullptr;
}
//----------------------------------------------------------------------------
const char *dir_entries::next()
{
    for(;;)
    {
        dirent *p;
        int err = ::readdir_r(dir, &entry, &p);
        if(err
#ifdef _AIX
            && err != 9 // no entries
#endif
        ) throw_errno("readdir_r", err);
        if(!p) return 0; // the end is reached
        if(!is_special(entry.d_name)) return entry.d_name;
    }
}
//----------------------------------------------------------------------------
void dir_entries::rewind()
{
    ::rewinddir(dir);
}
//----------------------------------------------------------------------------

}} // namespace
