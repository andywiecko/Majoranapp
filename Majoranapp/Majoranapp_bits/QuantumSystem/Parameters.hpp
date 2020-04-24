#ifndef QUANTUMSYSTEM_PARAMETERS_HPP
#define QUANTUMSYSTEM_PARAMETERS_HPP

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

};

#endif