//
// $Id$
//

#include<__vic/posix/fs.h>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void append_dirname(const std::string &path, std::string &res)
{
    std::string::size_type len = path.length();
    switch(len)
    {
        case 0: res += '.'; return;
        case 1: res += *path.begin() == '/' ? '/' : '.'; return;
    }
    // Precondition: length() > 1
    // Ignore trailing '/'
    std::string::size_type pos = path.rfind('/',
        path[len - 1] == '/' ? len - 2 : std::string::npos);
    switch(pos)
    {
        case 0: res += '/'; return;
        case std::string::npos: res += '.'; return;
    }
    res.append(path, 0, pos);
}
//----------------------------------------------------------------------------
std::string dirname(const std::string &path)
{
    std::string res;
    append_dirname(path, res);
    return res;
}
//----------------------------------------------------------------------------
void dirname(const std::string &path, std::string &res)
{
    res.clear();
    append_dirname(path, res);
}
//----------------------------------------------------------------------------

}} // namespace
