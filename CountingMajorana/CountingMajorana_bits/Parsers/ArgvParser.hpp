#ifndef PARSERS_ARGVPARSER_HPP
#define PARSERS_ARGVPARSER_HPP

#include <unistd.h>
#include <iostream>
#include "../Parameters.hpp"
#include "../Dimensions.hpp"
#include "KeyBindings.hpp"

#include "InputScriptParser.hpp"

/**
 * @brief primitive argv class
 */
class ArgvParser
{

private:
    /*
     * @brief increase verbosity of the output (flag)
     */
    bool verbose = false;

    /**
     * @brief show help (flag)
     */
    bool help = false;

public:

    /**
     * @brief parsed parameters
     */
    Parameters parameters;

    /**
     * @brief parsed parameters
     */
    Dimensions dimensions;

    /**
     * @brief construct a new Argv Parser object 
     */
    ArgvParser()
    {
        Info::Line();
        Info::ShowVersion();
        parameters.map[Spinfull::KineticTerm::name] = 1.0;
        parameters.map[Spinfull::ProxTerm::name] = 1.0;
        //dimensions.map[Dimensions::lengthName] = 10;
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
        Info::ShowMapCommonValue(KeyBindings::mapDimensions, dimensions.map);
        Info::Line();
        Info::Title("Parameters");
        Info::ShowMapCommonValue(KeyBindings::mapParameters, parameters.map);
        Info::Line();
    }

    /**
     * @brief 
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
        optstringKeys += ":vhf:";
        //std::cout << optstringKeys <<std::endl;
        const char *optstring = optstringKeys.c_str();
        

        while ((option = getopt(argc, argv, optstring)) != -1)
        {
            if (KeyBindings::mapDimensions.count(option) > 0)
        	{
                std::string name{KeyBindings::mapDimensions.at(option)};
                this->dimensions.map[name] = std::atof(optarg);
                continue;
            }

            if (KeyBindings::mapParameters.count(option) > 0)
        	{
                std::string name{KeyBindings::mapParameters.at(option)};
                this->parameters.map[name] = std::atof(optarg);
                continue;
            }

            if(option == 'v')
            {
                this->verbose = true;
                continue;
            }

            if(option == 'h')
            {
                this->help = true;
                continue;
            }

            if(option == 'f')
            {
                std::string filename = optarg;
                InputScriptParser::Parse(filename, parameters, dimensions);
                continue;
            }

            if(option == ':')
            {
                std::cout << "option requires argument\n";
                returnCode = 1;
                continue;
            }

            if(option == '?'){;}
            
            std::cout << "unknown option '" << char(optopt) << "'\n";
            returnCode = 1;
                    
        }

        for (; optind < argc; ++optind)
            std::cout << "argv[" << optind << "]='" << argv[optind] << "'\n";

        if (verbose)
            this->Info();

        if (help)
        {
            KeyBindings::Help();
            return 1;
        }

        VectorViewer::SetDimensions(dimensions);

        return returnCode;
    }
};

#endif
