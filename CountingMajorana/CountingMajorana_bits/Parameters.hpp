#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <string>
#include <map>

/**
 * @brief primitive class for storing uniform parameters
 */
class Parameters
{
public:
    /**
     * @brief map with parameters
     */
    std::map<std::string, double> map;

    /**
     * @brief Construct a new Parameters object
     */
    Parameters()
    {
        map["delta"] = 0.0;
        map["t_integral"] = 0.0;
        map["mu_potential"] = 0.0;
        map["zeeman"] = 0.0;
        map["rashbaX"] = 0.0;
        map["rashbaY"] = 0.0;
    }
};

#endif