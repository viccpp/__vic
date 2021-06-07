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

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
// Implementation base class
class dir_entries_base : private non_copyable
{
protected:
    DIR *dir;
    dir_entries_base(DIR *h = nullptr) : dir(h) {}
    ~dir_entries_base() { if(dir) ::closedir(dir); }
};
//////////////////////////////////////////////////////////////////////////////
// Directory entries observer
//////////////////////////////////////////////////////////////////////////////
class dir_entries : private dir_entries_base
{
    dirent *entry;
    static bool is_special(const char * );
    static dirent *alloc_dirent(const char * );
public:
    dir_entries() : entry(nullptr) {}
    explicit dir_entries(const char * );
    ~dir_entries();

#if __cpp_rvalue_references
    dir_entries(dir_entries &&o) noexcept
        : dir_entries_base(o.dir), entry(o.entry)
        { o.dir = nullptr; o.entry = nullptr; }
    dir_entries &operator=(dir_entries &&o) noexcept
    {
        std::swap(dir, o.dir);
        std::swap(entry, o.entry);
        return *this;
    }
#endif

    bool reopen(const char * );
    void close();
    bool is_open() const { return dir; }

    const char *next(); // returns entry name without path
#ifdef _DIRENT_HAVE_D_TYPE
    unsigned char type() const { return entry->d_type; }
#endif
    void rewind();
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
