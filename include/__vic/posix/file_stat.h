// <sys/stat.h> C++-wrapper
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2012

#ifndef __VIC_POSIX_FILE_STAT_H
#define __VIC_POSIX_FILE_STAT_H

#include<__vic/error.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string>

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
struct file_stat : public ::stat
{
    enum for_link_t { for_link };

    file_stat() __VIC_DEFAULT_CTR // uninitialized!
    typedef struct ::stat base; // Workaround for Clang's 3.5 bug
    file_stat(const struct ::stat &s) : base(s) {}
    explicit file_stat(int fd) { get(fd); }
    explicit file_stat(const char *path) { get(path); }
    explicit file_stat(const std::string &path) { get(path); }
    file_stat(const char *path, for_link_t) { get_for_link(path); }
    file_stat(const std::string &path, for_link_t) { get_for_link(path); }

    void get(int fd)
        { if(::fstat(fd, this)) throw_errno("fstat"); }
    void get(const char *path)
        { if(::stat(path, this)) throw_errno("stat"); }
    void get(const std::string &path)
        { get(path.c_str()); }
    void get_for_link(const char *path)
        { if(::lstat(path, this)) throw_errno("lstat"); }
    void get_for_link(const std::string &path)
        { get_for_link(path.c_str()); }

    bool try_get(int fd) { return !::fstat(fd, this); }
    bool try_get(const char *path) { return !::stat(path, this); }
    bool try_get(const std::string &path) { return try_get(path.c_str()); }
    bool try_get_for_link(const char *path) { return !::lstat(path, this); }
    bool try_get_for_link(const std::string &path)
        { return try_get_for_link(path.c_str()); }

    bool get_if_exists(const char * );
    bool get_if_exists(const std::string &path)
        { return get_if_exists(path.c_str()); }

    // POSIX-defined attributes
    dev_t   dev() const { return this->st_dev; }
    ino_t   ino() const { return this->st_ino; }
    mode_t  mode() const { return this->st_mode; }
    nlink_t nlink() const { return this->st_nlink; }
    uid_t   uid() const { return this->st_uid; }
    gid_t   gid() const { return this->st_gid; }
    off_t   size() const { return this->st_size; }
    time_t  atime() const { return this->st_atime; }
    time_t  mtime() const { return this->st_mtime; }
    time_t  ctime() const { return this->st_ctime; }

    bool is_block() const { return S_ISBLK(mode()); }
    bool is_char() const { return S_ISCHR(mode()); }
    bool is_dir() const { return S_ISDIR(mode()); }
    bool is_fifo() const { return S_ISFIFO(mode()); }
    bool is_regular() const { return S_ISREG(mode()); }
    bool is_link() const { return S_ISLNK(mode()); }
    bool is_socket() const { return S_ISSOCK(mode()); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline bool is_block(const struct ::stat &s) { return S_ISBLK(s.st_mode); }
inline bool is_char(const struct ::stat &s) { return S_ISCHR(s.st_mode); }
inline bool is_dir(const struct ::stat &s) { return S_ISDIR(s.st_mode); }
inline bool is_fifo(const struct ::stat &s) { return S_ISFIFO(s.st_mode); }
inline bool is_regular(const struct ::stat &s) { return S_ISREG(s.st_mode); }
inline bool is_link(const struct ::stat &s) { return S_ISLNK(s.st_mode); }
inline bool is_socket(const struct ::stat &s) { return S_ISSOCK(s.st_mode); }
//----------------------------------------------------------------------------
inline bool is_same_file(const struct ::stat &s1, const struct ::stat &s2)
{
    return s1.st_ino == s2.st_ino && s1.st_dev == s2.st_dev;
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
