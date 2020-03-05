#ifndef ARGV_PARSER_HPP
#define ARGV_PARSER_HPP

#include <unistd.h>
#include <iostream>

class ArgvParser
{

private:
    bool verbose = false;

public:
    int L = 10;
    double t_integral = 1.0;
    double delta = 1.0;
    double mu_potential = 0.0;
    double rashba = 0.0;
    double zeeman = 0.0;

    void Info()
    {
        std::cout << "# L = " << this->L << "\n";
        std::cout << "# t_integral = " << this->t_integral << "\n";
        std::cout << "# delta = " << this->delta << "\n";
        std::cout << "# mu_potential = " << this->mu_potential << "\n";
        std::cout << "# rashba = " << this->rashba << "\n";
        std::cout << "# zeeman = " << this->zeeman << "\n";
    }

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
                this->t_integral = std::atof(optarg);
                break;

            case 'd':
                this->delta = std::atof(optarg);
                break;

            case 'm':
                this->mu_potential = std::atof(optarg);
                break;

            case 'r':
                this->rashba = std::atof(optarg);
                break;

            case 'z':
                this->zeeman = std::atof(optarg);
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
