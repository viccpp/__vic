//
// $Id$
//

#include<__vic/posix/dir_entries.h>
#include<__vic/throw_errno.h>
#include<cerrno>

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
#ifdef __VIC_USE_READDIR
        errno = 0;
        if(dirent *p = ::readdir(dir))
        {
            if(!is_special(p->d_name))
            {
                entry = p;
                return p->d_name;
            }
        }
        else // no more entries or error
        {
            if(int err = errno) throw_errno("readdir", err);
            return nullptr; // the end is reached
        }
#else // use readdir_r()
        dirent *p;
        int err = ::readdir_r(dir, &entry, &p);
        if(err
#ifdef _AIX
            && err != 9 // no entries
#endif
        ) throw_errno("readdir_r", err);
        if(!p) return nullptr; // the end is reached
        if(!is_special(entry.d_name)) return entry.d_name;
#endif
    }
}
//----------------------------------------------------------------------------
void dir_entries::rewind()
{
    ::rewinddir(dir);
}
//----------------------------------------------------------------------------

}} // namespace
