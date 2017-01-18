//
// $Id
//

#include<__vic/posix/file.h>
#include<__vic/posix/file_stat.h>
#include<__vic/error.h>
#include<cstdio> // for BUFSIZ

namespace __vic {

//----------------------------------------------------------------------------
void write_fd_to_file(int fd_src, const char *dest_path, bool replace)
{
    posix::file dest(dest_path, O_WRONLY | O_CREAT |
            (replace ? O_TRUNC : O_EXCL), posix::file_stat(fd_src).mode());
    if(!dest.is_open()) throw_errno("Cannot create output file");

    char buf[BUFSIZ];
    size_t n;
    while(n = posix::file::read_some(fd_src, buf, sizeof buf))
        dest.write_all(buf, n);
    dest.close();
}
//----------------------------------------------------------------------------

} // namespace
