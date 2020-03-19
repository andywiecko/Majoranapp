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
    static const std::map<char, std::string> map;

    static void Help()
    {
        std::cout << "# key   name\n";
        std::cout << "# " << Lbinding << ": " << Ldescription << "\n";
        for (auto &[key, name] : KeyBindings::map)
        {
            std::cout << "# " << key << ": " + name + "\n";
        }
    }

    static std::string GetOptstring()
    {
        std::string ret = {':', Lbinding};
        for (auto const &item : KeyBindings::map)
        {
            ret += ":" + std::string{item.first};
        }
        return ret;
    }
};

const std::string KeyBindings::Ldescription{"L (sites)"};

const std::map<char, std::string> KeyBindings::map{
    {'t', "t_integral"},
    {'d', "delta"},
    {'m', "mu_potential"},
    {'x', "rashbaX"},
    {'r', "rashbaY"},
    {'z', "zeeman"}};

#endif