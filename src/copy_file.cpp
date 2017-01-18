//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/posix/file.h>
#include<__vic/throw_errno.h>

namespace __vic {

void write_fd_to_file(int , const char * , bool );

//----------------------------------------------------------------------------
void copy_file(const char *src_path, const char *dest_path, bool replace)
{
    posix::file src(src_path, O_RDONLY);
    if(!src.is_open()) throw_errno("Cannot open input file");
    write_fd_to_file(src.handle(), dest_path, replace);
    src.close();
}
//----------------------------------------------------------------------------

} // namespace
