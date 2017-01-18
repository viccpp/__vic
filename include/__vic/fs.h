// Filesystem utilities
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2012

#ifndef __VIC_FS_H
#define __VIC_FS_H

#include<__vic/defs.h>
#include<string>

namespace __vic {

//----------------------------------------------------------------------------
void copy_file(const char * , const char * , bool = false);
bool copy_file_if_exists(const char * , const char * , bool = false);
inline void copy_file_replace(const char *src_path, const char *dest_path)
{ copy_file(src_path, dest_path, true); }
inline bool copy_file_replace_if_exists(const char *src_path, const char *dest_path)
{ return copy_file_if_exists(src_path, dest_path, true); }
//----------------------------------------------------------------------------
inline void copy_file(
    const std::string &src_path, const std::string &dest_path, bool repl = false)
{
    copy_file(src_path.c_str(), dest_path.c_str(), repl);
}
inline bool copy_file_if_exists(
    const std::string &src_path, const std::string &dest_path, bool repl = false)
{
    return copy_file_if_exists(src_path.c_str(), dest_path.c_str());
}
inline void copy_file_replace(
    const std::string &src_path, const std::string &dest_path)
{
    copy_file_replace(src_path.c_str(), dest_path.c_str());
}
inline bool copy_file_replace_if_exists(
    const std::string &src_path, const std::string &dest_path)
{
    return copy_file_replace_if_exists(src_path.c_str(), dest_path.c_str());
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void move_file(const char * , const char * );
bool move_file_if_exists(const char * , const char * );
void move_file_replace(const char * , const char * );
bool move_file_replace_if_exists(const char * , const char * );
//----------------------------------------------------------------------------
inline void move_file(
    const std::string &src_path, const std::string &dest_path)
{
    move_file(src_path.c_str(), dest_path.c_str());
}
inline bool move_file_if_exists(
    const std::string &src_path, const std::string &dest_path)
{
    return move_file_if_exists(src_path.c_str(), dest_path.c_str());
}
inline void move_file_replace(
    const std::string &src_path, const std::string &dest_path)
{
    move_file_replace(src_path.c_str(), dest_path.c_str());
}
inline bool move_file_replace_if_exists(
    const std::string &src_path, const std::string &dest_path)
{
    return move_file_replace_if_exists(src_path.c_str(), dest_path.c_str());
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void rename_file(const char * , const char * );
bool rename_file_if_exists(const char * , const char * );
void rename_file_replace(const char * , const char * );
bool rename_file_replace_if_exists(const char * , const char * );
//----------------------------------------------------------------------------
inline void rename_file(
    const std::string &src_name, const std::string &dest_name)
{
    rename_file(src_name.c_str(), dest_name.c_str());
}
inline bool rename_file_if_exists(
    const std::string &src_name, const std::string &dest_name)
{
    return rename_file_if_exists(src_name.c_str(), dest_name.c_str());
}
inline void rename_file_replace(
    const std::string &src_name, const std::string &dest_name)
{
    rename_file_replace(src_name.c_str(), dest_name.c_str());
}
inline bool rename_file_replace_if_exists(
    const std::string &src_path, const std::string &dest_path)
{
    return rename_file_replace_if_exists(src_path.c_str(), dest_path.c_str());
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void remove_file(const char * );
bool remove_file_if_exists(const char * );
bool remove_file_nt(const char * ) noexcept;
//----------------------------------------------------------------------------
inline void remove_file(const std::string &path)
{ remove_file(path.c_str()); }
inline bool remove_file_if_exists(const std::string &path)
{ return remove_file_if_exists(path.c_str()); }
inline bool remove_file_nt(const std::string &path) noexcept
{ return remove_file_nt(path.c_str()); }
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
bool path_exists(const char * );
bool file_exists(const char * );
bool dir_exists(const char * );
//----------------------------------------------------------------------------
inline bool path_exists(const std::string &path)
{ return path_exists(path.c_str()); }
inline bool file_exists(const std::string &path)
{ return file_exists(path.c_str()); }
inline bool dir_exists(const std::string &path)
{ return dir_exists(path.c_str()); }
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void mkdir(const char * , mode_t = 0777);
bool mkdir_if_absent(const char * , mode_t = 0777);
//----------------------------------------------------------------------------
inline void mkdir(const std::string &path, mode_t mode = 0777)
{
    mkdir(path.c_str(), mode);
}
//----------------------------------------------------------------------------
inline bool mkdir_if_absent(const std::string &path, mode_t mode = 0777)
{
    return mkdir_if_absent(path.c_str(), mode);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void rmdir(const char * );
bool rmdir_if_exists(const char * );
//----------------------------------------------------------------------------
inline void rmdir(const std::string &path)
{
    rmdir(path.c_str());
}
//----------------------------------------------------------------------------
inline bool rmdir_if_exists(const std::string &path)
{
    return rmdir_if_exists(path.c_str());
}
//----------------------------------------------------------------------------

std::string get_current_dir();

} // namespace

#endif // header guard
