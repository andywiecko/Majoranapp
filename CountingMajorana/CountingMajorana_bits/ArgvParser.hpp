#ifndef ARGV_PARSER_HPP
#define ARGV_PARSER_HPP

#include <unistd.h>
#include <iostream>
#include "Parameters.hpp"

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
     * @brief parsed number of sites
     */
    int L = 10;
    /**
     * @brief parsed parameters
     */
    Parameters parameters;

    /**
     * @brief construct a new Argv Parser object 
     */
    ArgvParser()
    {
        parameters.map["t_integral"] = 1.0;
        parameters.map["delta"] = 1.0;
    }

    /**
     * @brief verbose info
     */
    void Info()
    {
        std::cout << "# L = " << this->L << "\n";
        std::cout << "# t_integral = " << this->parameters.map["t_integral"] << "\n";
        std::cout << "# delta = " << this->parameters.map["delta"] << "\n";
        std::cout << "# mu_potential = " << this->parameters.map["mu_potential"] << "\n";
        std::cout << "# rashba = " << this->parameters.map["rashba"] << "\n";
        std::cout << "# zeeman = " << this->parameters.map["zeeman"] << "\n";
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
        char optstring[] = ":L:t:d:m:r:z:v";

        while ((option = getopt(argc, argv, optstring)) != -1)
            switch (option)
            {
            case 'L':
                this->L = std::atoi(optarg);
                break;
            case 't':
                this->parameters.map["t_integral"] = std::atof(optarg);
                break;

            case 'd':
                this->parameters.map["delta"] = std::atof(optarg);
                break;

            case 'm':
                this->parameters.map["mu_potential"] = std::atof(optarg);
                break;

            case 'r':
                this->parameters.map["rashba"] = std::atof(optarg);
                break;

            case 'z':
                this->parameters.map["zeeman"] = std::atof(optarg);
                break;

            case 'v':
                this->verbose = true;
                break;
            case ':':
                std::cout << "option requires argument\n";
                returnCode = 1;
                break;
            case '?':
            default:
                std::cout << "unknown option '" << char(optopt) << "'\n";
                returnCode = 1;
                break;
            }

        for (; optind < argc; ++optind)
            std::cout << "argv[" << optind << "]='" << argv[optind] << "'\n";

        if (verbose)
            this->Info();

        return returnCode;
    }
};

#endif
