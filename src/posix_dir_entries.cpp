//
// $Id$
//

#include<__vic/posix/dir_entries.h>
#include<__vic/error.h>
#include<__vic/throw_errno.h>
#include<__vic/string_buffer.h>
#include<cerrno>
#include<new>
#include<cstddef> // for offsetof()
#include<unistd.h> // for pathconf()

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
    dir_entries_base(::opendir(path)),
    entry(alloc_dirent(path))
{
}
//----------------------------------------------------------------------------
dir_entries::~dir_entries()
{
    ::operator delete(entry);
}
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
bool dir_entries::reopen(const char *path)
{
    if(is_open()) close();
    DIR *d = ::opendir(path);
    if(!d) return false;
    try
    {
        dirent *ent = alloc_dirent(path);
        ::operator delete(entry);
        entry = ent;
    }
    catch(...)
    {
        ::closedir(d);
        throw;
    }
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
        int err = ::readdir_r(dir, entry, &p);
        if(err
#ifdef _AIX
            && err != 9 // no entries
#endif
        ) throw_errno("readdir_r", err);
        if(!p) return 0; // the end is reached
        if(!is_special(entry->d_name)) return entry->d_name;
    }
}
//----------------------------------------------------------------------------
void dir_entries::rewind()
{
    ::rewinddir(dir);
}
//----------------------------------------------------------------------------

}} // namespace
