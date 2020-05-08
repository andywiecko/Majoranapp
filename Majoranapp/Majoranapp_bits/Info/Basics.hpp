#ifndef INFO_BASICS_HPP
#define INFO_BASICS_HPP

#include <string>
#include <iostream>
#include <iomanip>

#include "Colors.hpp"
#include "Time.hpp"

/**
 * @brief Basic info functions
 */
class BasicsInfo
{
protected:
    /**
     * @brief standard comment string (default: #)
     */
    static const std::string comment;

public:
    /*
     * @brief increase verbosity of the output (flag)
     */
    static bool verbose;

    /**
     * @brief Display commented line
     * 
     * @param text text to display
     */
    static void Comment(std::string text)
    {
        std::cout << comment << text << "\n";
    }

    /**
     * @brief Comment for displaying map item
     * 
     * @tparam T1 type of key
     * @tparam T2 type of value
     * @param key item key
     * @param value item value
     */
    template <class T1, class T2>
    static void Comment(T1 key, T2 value)
    {
        std::cout << comment << "-" << key << " " << value << "\n";
    }

    /**
     * @brief Colored comment to std::clog with current program time
     * 
     * @param text text to log
     * @param color color of the text
     */
    static void LogComment(std::string text, std::string color)
    {
        if (BasicsInfo::verbose)
        {
            std::clog << std::fixed
                      << std::setprecision(6)
                      << std::setfill('0');
            std::clog << comment
                      << ColorsInfo::StartColor(color)
                      << "["
                      << std::setw(12) << TimeInfo::Time()
                      << "] "
                      << text
                      << ColorsInfo::StopColor()
                      << "\n";
        }
    }

    /**
     * @brief LogComment with red color
     * 
     * @param text 
     */
    static void LogBegining(std::string text)
    {
        BasicsInfo::LogComment(text, Color::red);
    }

    /**
     * @brief LogComment with green color
     * 
     * @param text 
     */
    static void LogAccomplished(std::string text = "... done")
    {
        BasicsInfo::LogComment(text, Color::green);
    }

    /**
     * @brief Warning sent to std::cout
     * 
     * @param text text to display (with red color)
     * @param note note (with white color)
     */
    static void Warning(std::string text, std::string note = "")
    {
        std::cout << ColorsInfo::Colorize("[!] " + text, Color::red)
                  << ColorsInfo::Colorize(note, Color::bwhite) << "\n";
    }

    /**
     * @brief Display title and Line
     * 
     * @param title 
     */
    static void Title(std::string title)
    {
        Comment(title);
        Line();
    }

    /**
     * @brief Display line of `n` char (default char '=')
     * 
     * @param n number of `=`
     */
    static void Line(int n = 40)
    {
        std::cout << comment << std::string(n, '=') << "\n";
    }
};

const std::string BasicsInfo::comment{"# "};
bool BasicsInfo::verbose{false};
#endif