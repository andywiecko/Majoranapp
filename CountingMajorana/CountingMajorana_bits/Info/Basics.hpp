#ifndef INFO_BASICS_HPP
#define INFO_BASICS_HPP

#include <string>
#include <iostream>
#include <iomanip>

#include "Colors.hpp"
#include "Time.hpp"

class BasicsInfo
{
protected:
    static const std::string comment;

public:
    /*
     * @brief increase verbosity of the output (flag)
     */
    static bool verbose;

    static void Comment(std::string text)
    {
        std::cout << comment << text << "\n";
    }

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

    static void LogBegining(std::string text)
    {
        BasicsInfo::LogComment(text, Color::red);
    }

    static void LogAccomplished(std::string text = "... done")
    {
        BasicsInfo::LogComment(text, Color::green);
    }

    static void Warning(std::string text, std::string note = "")
    {
        std::cout << ColorsInfo::Colorize("[!] " + text, Color::red)
                  << ColorsInfo::Colorize(note, Color::bwhite) << "\n";
    }

    static void Title(std::string title)
    {
        Comment(title);
        Line();
    }

    static void Line(int n = 40)
    {
        std::cout << comment << std::string(n, '=') << "\n";
    }
};

const std::string BasicsInfo::comment{"# "};
bool BasicsInfo::verbose{false};
#endif