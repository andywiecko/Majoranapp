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

    static const std::string lengthName;
    static const std::string heightName;
    static const std::string widthName;

    /**
     * @brief Construct a new Dimensions object
     */
    Dimensions()
    {
        map["Length"] = 10;
        map["Height"] = 1;
        map["Width"] = 1;
    }
};

const std::string Dimensions::lengthName{"Length"};
const std::string Dimensions::heightName{"Height"};
const std::string Dimensions::widthName{"Width"};

#endif