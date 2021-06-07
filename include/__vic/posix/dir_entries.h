// <dirent.h> C++-wrapper
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2010

#ifndef __VIC_POSIX_DIR_ENTRIES_H
#define __VIC_POSIX_DIR_ENTRIES_H

#include<__vic/defs.h>
#include<dirent.h>
#include<sys/types.h>

#if defined(__FreeBSD__) && !defined(_DIRENT_HAVE_D_TYPE)
#define _DIRENT_HAVE_D_TYPE 1
#endif

// Don't use readdir_r() since glibc-2.24 (Linux) and FreeBSD 12
#if (defined(__GLIBC__) && (__GLIBC__ == 2 && __GLIBC_MINOR >= 24) || __GLIBC__ > 2) || \
    (defined(__FreeBSD__) && __FreeBSD__ >= 12)
#define __VIC_USE_READDIR 1
#endif

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
// Directory entries observer
class dir_entries : private non_copyable
{
    DIR *dir;
#ifdef __VIC_USE_READDIR
    dirent *entry;
#else
    dirent entry;
#endif
    static bool is_special(const char * );
public:
    dir_entries() : dir(nullptr) {}
    explicit dir_entries(const char * );
    ~dir_entries();

#if __cpp_rvalue_references
    dir_entries(dir_entries &&o) noexcept :
        dir(o.dir), entry(o.entry) { o.dir = nullptr; }
    dir_entries &operator=(dir_entries &&o) noexcept
    {
        std::swap(dir, o.dir);
        entry = o.entry;
        return *this;
    }
#endif

    bool reopen(const char * );
    void close();
    bool is_open() const { return dir; }

    const char *next(); // returns entry name without path
#ifdef _DIRENT_HAVE_D_TYPE
    unsigned char type() const
    {
#ifdef __VIC_USE_READDIR
        return entry->d_type;
#else
        return entry.d_type;
#endif
    }
#endif
    void rewind();
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
