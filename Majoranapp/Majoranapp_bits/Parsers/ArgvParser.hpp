#ifndef PARSERS_ARGVPARSER_HPP
#define PARSERS_ARGVPARSER_HPP

#include <unistd.h>
#include <iostream>
#include "../QuantumSystem.hpp"
#include "KeyBindings.hpp"
#include "InputScriptParser.hpp"

/**
 * @brief primitive argv class
 */
class ArgvParser
{

private:
    /**
     * @brief show help (flag)
     */
    bool help = false;

    /**
     * @brief quiet mode (flag)
     */
    bool quiet = false;

public:
    /**
     * @brief all information about QuantumSystem parsed from argv and/or JSON inputscript
     */
    QuantumSystem quantumSystem;

    /**
     * @brief construct a new Argv Parser object 
     */
    ArgvParser()
    {
        quantumSystem.parameters.map[Spinfull::KineticTerm::name] = 1.0;
        quantumSystem.parameters.map[Spinfull::ProxTerm::name] = 1.0;
    }

    /**
     * @brief verbose info
     */
    void Info()
    {
        Info::Title("Model");
        Info::Comment(ModelSelector::GetSelected());
        Info::Line();
        Info::Title("Dimensions");
        Info::ShowMapCommonValue(KeyBindings::mapDimensions, quantumSystem.dimensions.map);
        Info::Line();
        Info::Title("Parameters");
        Info::ShowMapCommonValue(KeyBindings::mapParameters, quantumSystem.parameters.map);
        Info::Line();
        Info::Title("Connections");
        quantumSystem.parametersConnections.Print();
        Info::Line();
    }

    /**
     * @brief parsing argv
     * 
     * @param argc 
     * @param argv 
     * @return int parser's returnCode 
     */
    int Parse(int argc, char *argv[])
    {
        int option;
        int returnCode = 0;
        std::string optstringKeys = KeyBindings::GetOptstring();
        //optstringKeys += "vqhf:"; // TODO move to system key bindings
        const char *optstring = optstringKeys.c_str();

        while ((option = getopt(argc, argv, optstring)) != -1)
        {
            if (KeyBindings::mapDimensions.count(option) > 0)
            {
                std::string name{KeyBindings::mapDimensions.at(option)};
                quantumSystem.dimensions.map[name] = std::atof(optarg);
                continue;
            }

            if (KeyBindings::mapParameters.count(option) > 0)
            {
                std::string name{KeyBindings::mapParameters.at(option)};
                quantumSystem.parameters.map[name] = std::atof(optarg);
                continue;
            }

            if (option == KeyBindings::QuietKey)
            {
                quiet = true;
                continue;
            }

            if (option == KeyBindings::VerboseKey)
            {
                Info::verbose = true;
                continue;
            }

            if (option == KeyBindings::HelpKey)
            {
                help = true;
                continue;
            }

            if (option == KeyBindings::FilenameKey)
            {
                std::string filename = optarg;
                InputScriptParser::Parse(filename,
                                         quantumSystem);
                continue;
            }

            if (option == ':')
            {
                std::cout << "option requires argument\n";
                returnCode = 1;
                continue;
            }

            if (option == '?')
            {
                ;
            }

            std::cout << "unknown option '" << char(optopt) << "'\n";
            returnCode = 1;
        }

        for (; optind < argc; ++optind)
            std::cout << "argv[" << optind << "]='" << argv[optind] << "'\n";

        if (not quiet)
        {
            Info::Line();
            Info::ShowVersion();
        }


        if (Info::verbose)
            this->Info();

        if (help)
        {
            KeyBindings::Help();
            return 1;
        }

        VectorViewer::SetDimensions(quantumSystem.dimensions);

        return returnCode;
    }
};

#endif
