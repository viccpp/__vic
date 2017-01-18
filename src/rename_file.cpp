//
// $Id$
//

#include<__vic/fs.h>
#include<windows.h>

namespace __vic {

void move_file_(const char * , const char * , DWORD );

//----------------------------------------------------------------------------
void rename_file(const char *src_path, const char *dest_path)
{
    move_file_(src_path, dest_path, 0);
}
//----------------------------------------------------------------------------
void rename_file_replace(const char *src_path, const char *dest_path)
{
    move_file_(src_path, dest_path, MOVEFILE_REPLACE_EXISTING);
}
//----------------------------------------------------------------------------

} // namespace
