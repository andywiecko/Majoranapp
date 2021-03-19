#ifndef PARSERS_KEYBINDINGS_HPP
#define PARSERS_KEYBINDINGS_HPP

#include <iostream>
#include <map>
#include <string>

#include "../Info.hpp"
#include "../Filler.hpp"

#include "SystemOption.hpp"

/**
 * @brief Key bindings for char and selected terms, dimensions and TODO system options
 */
class KeyBindings
{
public:
    /**
     * @brief Dimensions translation map
     */
    static const std::map<char, std::string> mapDimensions;
    /**
     * @brief Parameters name translation map
     */
    static const std::map<char, std::string> mapParameters;
    /**
     * @brief SystemKeys name translation map
     */
    static const std::map<char, SystemOption> mapSystemKeys;

    /**
     * @brief display all key bindings
     */
    static void Help()
    {
        Info::Comment("Program options");
        Info::Comment("opt ARG description");
        Info::Line();
        Info::ShowMap(KeyBindings::mapSystemKeys);
        Info::Line();
        Info::Comment("Parameters settings");
        Info::Comment("key   name");
        Info::Line();
        Info::ShowMap(KeyBindings::mapDimensions);
        Info::ShowMap(KeyBindings::mapParameters);
        Info::Line();
        Info::Comment("Example");
        Info::Line();
        Info::Comment("The following command will run program with");
        Info::Comment("settings and parameters loaded from JSON");
        Info::Comment("and the Length will be replaced by 100:");
        Info::Comment("");
        Info::Comment("./majoranapp.exe -f inputscript.json -L 100");
    }

    /**
     * @brief Get the Optstring object
     * optstring for ArgvParser
     * 
     * @return std::string 
     */
    static std::string GetOptstring()
    {
        std::string ret{":"};
        for (auto const &item : KeyBindings::mapDimensions)
        {
            ret += std::string{item.first} + ":";
        }
        for (auto const &item : KeyBindings::mapParameters)
        {
            ret += std::string{item.first} + ":";
        }
        for (auto const &item : KeyBindings::mapSystemKeys)
        {
            ret += std::string{item.first} + item.second.opt;
        }
        return ret;
    }

    static const char VerboseKey{'v'};
    static const char HelpKey{'h'};
    static const char QuietKey{'q'};
    static const char FilenameKey{'f'};

};

const std::map<char, SystemOption> KeyBindings::mapSystemKeys{
    {KeyBindings::VerboseKey, {"verbose","increase output verbosity",""}},
    {KeyBindings::FilenameKey, {"filename","select inputscript filename",":"}},
    {KeyBindings::QuietKey, {"quiet","decrease output verbosity",""}},
    {KeyBindings::HelpKey, {"help","show help page",""}}
    };

const std::map<char, std::string> KeyBindings::mapDimensions{
    {'L', Dimensions::lengthName},
    {'W', Dimensions::widthName},
    {'H', Dimensions::heightName}};

const std::map<char, std::string> KeyBindings::mapParameters{
    {'t', Spinfull::KineticTerm::name},
    {'d', Spinfull::ProxTerm::name},
    {'m', Spinfull::ChemicalTerm::name},
    {'X', Spinfull::RashbaXTerm::name},
    {'Y', Spinfull::RashbaYTerm::name},
    {'Z', Spinfull::RashbaZTerm::name},
    {'x', Spinfull::ZeemanXTerm::name},
    {'y', Spinfull::ZeemanYTerm::name},
    {'z', Spinfull::ZeemanZTerm::name},
    {'p', "magnetic_field"}};

#endif