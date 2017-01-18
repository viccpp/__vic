//
// $Id$
//

#include<__vic/fs.h>
#include<windows.h>

namespace __vic {

void move_file_(const char * , const char * , DWORD );

//----------------------------------------------------------------------------
void move_file(const char *src_path, const char *dest_path)
{
    move_file_(src_path, dest_path, MOVEFILE_COPY_ALLOWED);
}
//----------------------------------------------------------------------------
void move_file_replace(const char *src_path, const char *dest_path)
{
    move_file_(src_path, dest_path,
        MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING);
}
//----------------------------------------------------------------------------

} // namespace
