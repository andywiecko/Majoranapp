#ifndef DIMENSIONS_HPP
#define DIMENSIONS_HPP

#include <string>
#include <map>

/**
 * @brief primitive class for storing cube dimensions
 */
class Dimensions
{
public:
    /**
     * @brief map with dimensions
     */
    std::map<std::string, int> map;

    /**
     * @brief Construct a new Dimensions object
     */
    Dimensions()
    {
        map["Length"] = 10;
        map["Width"] = 1;
        map["Height"] = 1;
    }
};

#endif