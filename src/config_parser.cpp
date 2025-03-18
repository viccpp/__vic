//
// $Id$
//

#if __cplusplus >= 201103L // C++11

#include<__vic/config/parser.h>
#include<__vic/stdio_file.h>
#include<__vic/string_utils.h>
#include<__vic/error.h>
#include<cassert>

namespace __vic { namespace config {

//////////////////////////////////////////////////////////////////////////////
class parser::file_source : public source
{
    unsigned line_ = 0;
    stdio_file file;
    // tmp buffers
    string_buffer buf{256}, name{32}, value{64};

    void put_param(abstract_value * , const std::string & );
public:
    explicit file_source(const char *fname) : file(fname, "r")
    {
        if(!file.is_open()) throw error(msg(256) <<
            "Couldn't open config file \"" << fname << '"');
    }

    bool read_line(std::string &s)
    {
        if(!getline(file, s)) return false;
        line_++;
        return true;
    }
    unsigned line() const { return line_; }

    void read(parser & , bool );
    void read(parser & ) override;
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
parser::parser()
{
}
//----------------------------------------------------------------------------
parser::~parser()
{
}
//---------------------------------------------------------------------------
void parser::throw_invalid_format(unsigned line)
{
    throw source_error(line, "Invalid format");
}
//---------------------------------------------------------------------------
void parser::add_param(const char *name, std::unique_ptr<abstract_value> param)
{
    bool inserted = params.insert(decltype(params)::
        value_type(name, std::move(param))).second;
    if(!inserted) throw duplicate_param();
}
//---------------------------------------------------------------------------
abstract_value *parser::find_param(const std::string &name) const
{
    auto it = params.find(name);
    return it != params.end() ? &*it->second : nullptr;
}
//----------------------------------------------------------------------------
void parser::file_source::put_param(
    abstract_value *param, const std::string &value)
{
    if(!param->parse(value))
        throw source_error(line(), "Invalid config parameter value");
}
//----------------------------------------------------------------------------
inline void parser::include(string_buffer &file, unsigned line)
{
    if(file.length() < 3 || file.back() != '>') throw_invalid_format(line);
    file.back() = '\x0';
    try {
        parse(file.c_str() + 1);
    } catch(const source_error &ex) {
        throw source_error(ex, msg(64) <<
            '<' << file.c_str() + 1 << ">: " << ex.what());
    }
}
//----------------------------------------------------------------------------
void parser::file_source::read(config::parser &parser, bool on_top)
{
    enum class param_style { colon, brace, paren, multiline };
    while(read_line(buf))
    {
        trim(buf);
        // skip empty lines and comments
        if(buf.empty() || buf.front() == '#') continue;
        if(buf.front() == ')')
        {
            if(on_top) throw_invalid_format(line());
            return;
        }
        if(buf.front() == '<')
        {
            parser.include(buf, line());
            continue;
        }
        // parse param name
        std::string::size_type delim_pos = buf.find(':');
        auto style = param_style::colon;
        if(delim_pos == std::string::npos)
        {
            assert(!buf.empty());
            switch(buf.back())
            {
                case '{':
                    delim_pos = buf.length() - 1;
                    style = param_style::brace;
                    break;
                case '(':
                    delim_pos = buf.length() - 1;
                    style = param_style::paren;
                    break;
                default: // may be it's multiline string
                    delim_pos = buf.find("<<");
                    if(delim_pos == std::string::npos)
                        throw_invalid_format(line());
                    style = param_style::multiline;
            }
        }
        name.assign(buf, 0, delim_pos);
        trim(name);
        if(name.empty()) throw_invalid_format(line());
        abstract_value *param = parser.find_param(name);
        if(!param) throw source_error(line(), msg(64) <<
            "Unknown config parameter \"" << name << '"');
        // parse param value(s)
        switch(style)
        {
            case param_style::colon: // :
                value.assign(buf, delim_pos+1, buf.max_size());
                trim(value);
                put_param(param, value);
                break;
            case param_style::brace: // {
            {
                if(!param->is_list()) throw source_error(line(),
                    "\"{\" is used for non-list parameter");
                bool is_complex = param->is_complex();
                // Parse a list of values
                for(;;)
                {
                    if(!read_line(buf)) throw error(msg(128) <<
                        "Incomplete list \"" << name <<
                        "\": no closing \"}\" delimiter found");
                    trim(buf);
                    if(buf == "}") break;
                    // skip empty lines and comments
                    if(buf.empty() || buf.front() == '#') continue;
                    if(is_complex)
                    {
                        if(buf != "(") throw source_error(line(),
                            "\"(\" has to be used for complex parameter");
                        param->parse(*this);
                    }
                    else put_param(param, buf);
                }
                break;
            }
            case param_style::paren: // (
                if(!param->is_complex()) throw source_error(line(),
                    "\"(\" is used for non-complex parameter");
                param->parse(*this);
                break;
            case param_style::multiline: // <<
            {
                std::string delim(buf, delim_pos+2);
                trim(delim);
                value.clear();
                // Read content
                for(;;)
                {
                    if(!read_line(buf)) throw error(msg(128) <<
                        "Incomplete multiline parameter \"" << name <<
                        "\": no param delimiter \"" << delim << "\" found");
                    if(buf == delim) break;
                    value << buf << '\n';
                }
                put_param(param, value);
                break;
            }
        }
    }
    if(!on_top) throw error(
        "Incomplete complex parameter: no closing \")\" delimiter found");
}
//----------------------------------------------------------------------------
void parser::file_source::read(parser &p)
{
    read(p, false);
}
//----------------------------------------------------------------------------
void parser::parse(const char *fname)
{
    file_source file(fname);
    file.read(*this, true);
}
//---------------------------------------------------------------------------
const char *parser::duplicate_param::what() const noexcept
{
    return "Duplicate config parameter";
}
//----------------------------------------------------------------------------

}} // namespace

#endif // C++11
