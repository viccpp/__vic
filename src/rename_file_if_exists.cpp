//
// $Id$
//

#include<__vic/fs.h>
#include<windows.h>

namespace __vic {

bool move_file_if_exists_(const char * , const char * , DWORD );

//----------------------------------------------------------------------------
bool rename_file_if_exists(const char *src_path, const char *dest_path)
{
    return move_file_if_exists_(src_path, dest_path, 0);
}
//----------------------------------------------------------------------------
bool rename_file_replace_if_exists(
    const char *src_path, const char *dest_path)
{
    return move_file_if_exists_(src_path, dest_path, MOVEFILE_REPLACE_EXISTING);
}
//----------------------------------------------------------------------------

} // namespace
