//
// $Id$
//

#include<__vic/posix/dir_entries.h>
#include<__vic/throw_errno.h>
#include<__vic/string_buffer.h>
#include<cerrno>
#ifndef __VIC_USE_READDIR
#include<__vic/error.h>
#include<new>
#include<cstddef> // for offsetof()
#include<unistd.h> // for pathconf()
#endif

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
// True for "." and ".." entries
inline bool dir_entries::is_special(const char *f)
{
    return *f == '.' && (f[1] == '\0' || (f[1] == '.' && f[2] == '\0'));
}
//----------------------------------------------------------------------------
dir_entries::dir_entries(const char *path)
:
    dir_entries_base(::opendir(path))
#ifndef __VIC_USE_READDIR
    , entry(alloc_dirent(path))
#endif
{
}
//----------------------------------------------------------------------------
dir_entries::~dir_entries()
{
#ifndef __VIC_USE_READDIR
    ::operator delete(entry);
#endif
}
//----------------------------------------------------------------------------
#ifndef __VIC_USE_READDIR
dirent *dir_entries::alloc_dirent(const char *path)
{
    errno = 0;
    long name_max = ::pathconf(path, _PC_NAME_MAX);
    if(name_max < 0)
    {
        int err = errno;
        if(err) throw_errno("pathconf(_PC_NAME_MAX)", err);
        throw exception("pathconf(_PC_NAME_MAX) is indefinite");
    }
    size_t len = offsetof(dirent, d_name) +
                    static_cast<size_t>(name_max) + 1U;
    return static_cast<dirent*>(::operator new(len));
}
#endif
//----------------------------------------------------------------------------
bool dir_entries::reopen(const char *path)
{
    if(is_open()) close();
    DIR *d = ::opendir(path);
    if(!d) return false;
#ifndef __VIC_USE_READDIR
    try {
        entry = alloc_dirent(path);
    } catch(...) {
        ::closedir(d);
        throw;
    }
#endif
    dir = d;
    return true;
}
//----------------------------------------------------------------------------
void dir_entries::close()
{
    if(::closedir(dir)) throw_errno("closedir");
    dir = nullptr;
#ifndef __VIC_USE_READDIR
    ::operator delete(entry);
    entry = nullptr;
#endif
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
        int err = ::readdir_r(dir, entry, &p);
        if(err
#ifdef _AIX
            && err != 9 // no entries
#endif
        ) throw_errno("readdir_r", err);
        if(!p) return nullptr; // the end is reached
        if(!is_special(entry->d_name)) return entry->d_name;
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
