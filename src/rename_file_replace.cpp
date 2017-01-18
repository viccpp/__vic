//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/throw_errno.h>
#include<cstdio>

//----------------------------------------------------------------------------
void __vic::rename_file_replace(const char *src_name, const char *dest_name)
{
    if(std::rename(src_name, dest_name)) throw_errno("rename");
}
//----------------------------------------------------------------------------
