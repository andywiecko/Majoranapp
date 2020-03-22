#ifndef KEYBINDINGS_HPP
#define KEYBINDINGS_HPP

#include <iostream>
#include <map>
#include <string>

#include "Info.hpp"
#include "Filler.hpp"

class KeyBindings
{
public:
    static const std::map<char, std::string> mapDimensions;
    static const std::map<char, std::string> mapParameters;

    static void Help()
    {
        std::cout << "# key   name\n";
        Info::ShowMap(KeyBindings::mapDimensions);
        Info::ShowMap(KeyBindings::mapParameters);

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
    {'L', Dimensions::lengthName},
    {'W', Dimensions::widthName},
    {'H', Dimensions::heightName}};

const std::map<char, std::string> KeyBindings::mapParameters{
    {'t', Spinfull::KineticTerm::name},
    {'d', Spinfull::ProxTerm::name},
    {'m', Spinfull::ChemicalTerm::name},
    {'x', Spinfull::RashbaXTerm::name},
    {'r', Spinfull::RashbaYTerm::name},
    {'s', Spinfull::SpinFlipTerm::name},
    {'z', Spinfull::ZeemanTerm::name}};

#endif