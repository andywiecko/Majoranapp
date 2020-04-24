#ifndef INFO_DIMENSIONSWARNING_HPP
#define INFO_DIMENSIONSWARNING_HPP

#include "Basics.hpp"

/**
 * @brief A few warnings for parsed dimensions
 */
class DimensionsWarningInfo
{
public:
    /**
     * @brief checks if height and width are equal 0
     * 
     * @param length 
     * @param width 
     * @param height 
     */
    static void DimensionsWarningOnly1D(int length, int width, int height)
    {
        if (width > 1 or height > 1)
        {
            BasicsInfo::Warning("One dimensional model is selected. ",
                                "Width and Height values are ignored!");
        }
    }

    /**
     * @brief checks if height is equal 0
     * 
     * @param length 
     * @param width 
     * @param height 
     */
    static void DimensionsWarningOnly2D(int length, int width, int height)
    {
        if (height > 1)
        {
            BasicsInfo::Warning("Two dimensional model is selected. ",
                                "Height value is ignored!");
        }
    }
};

#endif