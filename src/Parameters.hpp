#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <string>
#include <map>

class Parameters
{
public:
    std::map<std::string, double> map;

    Parameters()
    {
        map["delta"] = 0.0;
        map["t_integral"] = 0.0;
        map["mu_potential"] = 0.0;
        map["zeeman"] = 0.0;
        map["rashba"] = 0.0;
    }
};

#endif