#ifndef INFO_BASICS_HPP
#define INFO_BASICS_HPP

#include <string>
#include <iostream>

class BasicsInfo
{
protected:
    static const std::string comment;

public:

    static void Comment(std::string text)
    {
        std::cout << comment << text << "\n";
    }

    static void Title(std::string title)
    {
        Line();
        Comment(title);
        Line();
    }

    static void Line()
    {
        std::cout << comment << std::string(15,'=') << "\n";
    }
};

const std::string BasicsInfo::comment{"# "};

#endif