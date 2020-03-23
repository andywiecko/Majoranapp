#ifndef INFO_COLORS_HPP
#define INFO_COLORS_HPP

#include <string>

class Color
{
public:
    static const std::string green;
    static const std::string red;
    static const std::string blue;
    static const std::string bwhite;
    static const std::string normal;
};

class ColorsInfo
{
public:
    static std::string Colorize(std::string text, std::string color)
    {
        return color + text + Color::normal;
    }
};

const std::string Color::green{"\033[0;32m"};
const std::string Color::red{"\033[0;31m"};
const std::string Color::blue{"\033[0;34m"};
const std::string Color::bwhite{"\033[1;37m"};
const std::string Color::normal{"\033[0m"};


#endif