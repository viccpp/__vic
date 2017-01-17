//
// $Id$
//

#include<__vic/posix/fs.h>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void append_basename(const std::string &path, std::string &res)
{
    std::string::const_iterator end = path.end();
    // Skip all trailing slashes
    while(end > path.begin() + 1 && *(end - 1) == '/') end--;
    if(end == path.begin() + 1 && *path.begin() == '/')
        { res += '/'; return; } // only one '/'
    std::string::size_type pos = path.rfind('/', end - path.begin() - 1);
    if(pos == std::string::npos)
        res.append(path, 0, end - path.begin());
    else
        res.append(path, pos + 1, end - (path.begin() + pos + 1));
}
//----------------------------------------------------------------------------
std::string basename(const std::string &path)
{
    std::string res;
    append_basename(path, res);
    return res;
}
//----------------------------------------------------------------------------
void basename(const std::string &path, std::string &res)
{
    res.clear();
    append_basename(path, res);
}
//----------------------------------------------------------------------------

}} // namespace
