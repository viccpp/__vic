//
// $Id$
//

#include<__vic/io.h>

namespace __vic {

//----------------------------------------------------------------------------
bool getline(std::FILE *fp, std::string &buf, char delim)
{
    char ch;
    if(!read(fp, ch)) return false; // end-of-file
    buf.clear();
    do {
        if(ch == delim) break;
        buf.push_back(ch);
    } while(read(fp, ch));
    return true;
}
//----------------------------------------------------------------------------

} // namespace
