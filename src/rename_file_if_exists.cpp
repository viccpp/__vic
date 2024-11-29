//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/windows/wchar.h>
#include<windows.h>

namespace __vic {

bool move_file_if_exists_(const wchar_t * , const wchar_t * , DWORD );

//----------------------------------------------------------------------------
bool rename_file_if_exists(const wchar_t *src_path, const wchar_t *dest_path)
{
    return move_file_if_exists_(src_path, dest_path, 0);
}
//----------------------------------------------------------------------------
bool rename_file_replace_if_exists(
    const wchar_t *src_path, const wchar_t *dest_path)
{
    return move_file_if_exists_(src_path, dest_path, MOVEFILE_REPLACE_EXISTING);
}
//----------------------------------------------------------------------------
bool rename_file_if_exists(const char *src_path, const char *dest_path)
{
    using windows::utf8to16;
    return rename_file_if_exists(utf8to16(src_path), utf8to16(dest_path));
}
//----------------------------------------------------------------------------
bool rename_file_replace_if_exists(
    const char *src_path, const char *dest_path)
{
    return rename_file_replace_if_exists(
        windows::utf8to16(src_path), windows::utf8to16(dest_path));
}
//----------------------------------------------------------------------------

} // namespace
