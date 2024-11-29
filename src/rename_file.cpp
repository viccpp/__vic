//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<windows.h>

namespace __vic {

void move_file_(const wchar_t * , const wchar_t * , DWORD );

//----------------------------------------------------------------------------
void rename_file(const wchar_t *src_path, const wchar_t *dest_path)
{
    move_file_(src_path, dest_path, 0);
}
//----------------------------------------------------------------------------
void rename_file_replace(const wchar_t *src_path, const wchar_t *dest_path)
{
    move_file_(src_path, dest_path, MOVEFILE_REPLACE_EXISTING);
}
//----------------------------------------------------------------------------
void rename_file(const char *src_path, const char *dest_path)
{
    using windows::utf8to16;
    rename_file(utf8to16(src_path), utf8to16(dest_path));
}
//----------------------------------------------------------------------------
void rename_file_replace(const char *src_path, const char *dest_path)
{
    using windows::utf8to16;
    rename_file_replace(utf8to16(src_path), utf8to16(dest_path));
}
//----------------------------------------------------------------------------

} // namespace
