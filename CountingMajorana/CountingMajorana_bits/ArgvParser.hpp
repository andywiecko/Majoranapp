#ifndef ARGV_PARSER_HPP
#define ARGV_PARSER_HPP

#include <unistd.h>
#include <iostream>
#include "Parameters.hpp"
#include "Dimensions.hpp"
#include "KeyBinding.hpp"

/**
 * @brief primitive argv class
 */
class ArgvParser
{

private:
    /**
     * @brief increase verbosity of the output
     */
    bool verbose = false;

public:

    /**
     * @brief parsed parameters
     */
    Parameters parameters;

    Dimensions dimensions;

    /**
     * @brief construct a new Argv Parser object 
     */
    ArgvParser()
    {
        parameters.map["t_integral"] = 1.0;
        parameters.map["delta"] = 1.0;
        dimensions.map["Length"] = 10;
    }

    /**
     * @brief verbose info
     */
    void Info()
    {
        // TODO make Info class [!]
        std::cout << "# "<<std::string(15,'=') << "\n"<< "# Dimensions\n# "<< std::string(15,'=') << "\n";
        for(const auto &item: KeyBindings::mapDimensions)
        {
            std::cout << "# "<< item.second << " = " << dimensions.map[item.second] << "\n";
        }

        std::cout << "# "<<std::string(15,'=') << "\n"<< "# Parameters\n# " << std::string(15,'=') << "\n";
        for(const auto &item: KeyBindings::mapParameters)
        {
            std::cout << "# "<< item.second << " = " << parameters.map[item.second] << "\n";
        }
        std::cout << "# "<<std::string(15,'=') << "\n";
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
        optstringKeys += ":vh";
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
                KeyBindings::Help();
                // TODO exit here!
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

        return returnCode;
    }
};

#endif
