#ifndef KEYBINDINGS_HPP
#define KEYBINDINGS_HPP

#include <iostream>
#include <map>
#include <string>

#include "Filler.hpp"

class KeyBindings
{
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

const std::map<char, std::string> KeyBindings::mapDimensions{
    {'L', "Length"},
    {'W', "Width"},
    {'H', "Height"}};

const std::map<char, std::string> KeyBindings::mapParameters{
    {'t', Spinfull::KineticTerm::name},
    {'d', Spinfull::ProxTerm::name},
    {'m', Spinfull::ChemicalTerm::name},
    {'x', Spinfull::RashbaXTerm::name},
    {'r', Spinfull::RashbaYTerm::name},
    {'f', Spinfull::SpinFlipTerm::name},
    {'z', Spinfull::ZeemanTerm::name}};

#endif