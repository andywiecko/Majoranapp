#ifndef INFO_COLORS_HPP
#define INFO_COLORS_HPP

#include <string>

/**
 * @brief static class containing a few color definitions
 * 
 */
class Color
{
public:
    static const std::string green;
    static const std::string red;
    static const std::string blue;
    static const std::string bwhite;
    static const std::string normal;
};

/**
 * @brief Colorizing the text
 */
class ColorsInfo
{
public:
    /**
     * @brief Add prefix and suffix for color display in Linux terminal
     * 
     * @param text to color
     * @param color selected color
     * @return std::string of colorized text
     */
    static std::string Colorize(std::string text, std::string color)
    {
        return color + text + Color::normal;
    }

    /**
     * @brief returns selected color
     * 
     * @param color to return
     * @return std::string color
     */
    static std::string StartColor(std::string color)
    {
        return color;
    }
    /**
     * @brief resets color to default `normal`
     * 
     * @return std::string return normal
     */
    static std::string StopColor()
    {
        return Color::normal;
    }
};

const std::string Color::green{"\033[0;32m"};
const std::string Color::red{"\033[0;31m"};
const std::string Color::blue{"\033[0;34m"};
const std::string Color::bwhite{"\033[1;37m"};
const std::string Color::normal{"\033[0m"};


#endif