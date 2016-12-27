// Directory files observer (The same as dir_enries but subdirs are ignored)
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_POSIX_DIR_FILES_H
#define __VIC_POSIX_DIR_FILES_H

#include<__vic/defs.h>
#include<__vic/posix/dir_entries.h>
#include<__vic/string_buffer.h>
#include<string>

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
class dir_files : private non_copyable
{
    dir_entries de;
    std::string dir, pattern;
    string_buffer tmp; // for full path string building
public:
    dir_files();
    explicit dir_files(const char * , const char * = nullptr);
    ~dir_files();

#if __cpp_rvalue_references
    dir_files(dir_files && ) noexcept;
    dir_files &operator=(dir_files && ) noexcept;
#endif

    void reopen(const char * , const char * = nullptr);
    void close() { de.close(); }
    bool is_open() const { return de.is_open(); }

    const char *next(); // returns filename without path
    void rewind() { de.rewind(); }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
