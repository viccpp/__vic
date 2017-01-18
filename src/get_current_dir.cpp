//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/throw_errno.h>
#include<limits.h> // for PATH_MAX
#include<unistd.h>

//----------------------------------------------------------------------------
std::string __vic::get_current_dir()
{
    char buf[PATH_MAX];
    if(!::getcwd(buf, sizeof buf)) throw_errno("getcwd");
    return buf;
}
//----------------------------------------------------------------------------
