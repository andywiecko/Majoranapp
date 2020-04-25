#ifndef PARSERS_SYSTEMOPTION
#define PARSERS_SYSTEMOPTION

#include <string>

class SystemOption
{
public:
    std::string name;
    std::string description;
    std::string opt;
    SystemOption(std::string _name,
                 std::string _desc,
                 std::string _opt) : name{_name}, description{_desc}, opt{_opt}
    {
    }
};

std::ostream &operator<<(std::ostream &out, SystemOption systemOption)
{
    if (systemOption.opt == ":")
        out << "[ARG] ";
    else
        out << "      ";
    out << systemOption.name << ": " << systemOption.description;
    return out;
}

#endif