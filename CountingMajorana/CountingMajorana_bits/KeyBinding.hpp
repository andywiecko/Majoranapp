#ifndef KEYBINDINGS_HPP
#define KEYBINDINGS_HPP

#include <iostream>
#include <map>
#include <string>

class KeyBindings
{
private:
    static const char Lbinding = 'L';
    static const std::string Ldescription;

public:
    static const std::map<char, std::string> mapDimensions;
    static const std::map<char, std::string> mapParameters;

    static void Help()
    {
        std::cout << "# key   name\n";
        for (auto &[key, name] : KeyBindings::mapDimensions)
        {
            std::cout << "# " << key << ": " + name + "\n";
        }
        for (auto &[key, name] : KeyBindings::mapParameters)
        {
            std::cout << "# " << key << ": " + name + "\n";
        }
    }

    static std::string GetOptstring()
    {
        std::string ret;
        for (auto const &item : KeyBindings::mapDimensions)
        {
            ret += ":" + std::string{item.first};
        }
        for (auto const &item : KeyBindings::mapParameters)
        {
            ret += ":" + std::string{item.first};
        }
        return ret;
    }
};

const std::string KeyBindings::Ldescription{"L (sites)"};

const std::map<char, std::string> KeyBindings::mapDimensions{
    {'L', "Length"},
    {'W', "Width"},
    {'H', "Height"}};

const std::map<char, std::string> KeyBindings::mapParameters{
    {'t', "t_integral"},
    {'d', "delta"},
    {'m', "mu_potential"},
    {'x', "rashbaX"},
    {'r', "rashbaY"},
    {'z', "zeeman"}};

#endif