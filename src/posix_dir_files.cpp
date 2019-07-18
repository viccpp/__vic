//
// $Id$
//

#include<__vic/posix/dir_files.h>
#include<__vic/posix/file_stat.h>
#include<fnmatch.h>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
dir_files::dir_files()
{
}
//----------------------------------------------------------------------------
dir_files::dir_files(const char *path, const char *patt)
    : de(path), dir(path)
{
    if(patt) pattern = patt;
}
//----------------------------------------------------------------------------
dir_files::~dir_files()
{
}
//----------------------------------------------------------------------------
#if __cpp_rvalue_references
//----------------------------------------------------------------------------
dir_files::dir_files(dir_files &&o) noexcept
:
    de(std::move(o.de)),
    dir(std::move(o.dir)),
    pattern(std::move(o.pattern))
{
}
//----------------------------------------------------------------------------
dir_files &dir_files::operator=(dir_files &&o) noexcept
{
    if(&o != this)
    {
        de = std::move(o.de);
        dir = std::move(o.dir);
        pattern = std::move(o.pattern);
    }
    return *this;
}
//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
bool dir_files::reopen(const char *path, const char *patt)
{
    if(!de.reopen(path)) return false;
    dir = path;
    if(patt) pattern = patt; else pattern.clear();
    return true;
}
//----------------------------------------------------------------------------
const char *dir_files::next()
{
    while(const char *entry = de.next())
    {
        if(pattern.empty() || ::fnmatch(pattern.c_str(), entry, 0) == 0)
        {
            // is it a regular file?
#ifdef _DIRENT_HAVE_D_TYPE
            switch(de.type())
            {
                case DT_REG: return entry;
                case DT_UNKNOWN: break; // can't detect - use stat()
                default: continue;
            }
#endif
            tmp.clear() << dir << '/' << entry;
            file_stat s;
            if(s.get_if_exists(tmp) && s.is_regular()) return entry;
            // ignore disappeared entries
        }
    }
    return 0;
}
//----------------------------------------------------------------------------

}} // namespace
