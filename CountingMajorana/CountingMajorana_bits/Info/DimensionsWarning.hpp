#ifndef INFO_DIMENSIONSWARNING_HPP
#define INFO_DIMENSIONSWARNING_HPP

#include "Basics.hpp"

class DimensionsWarningInfo
{
public:
    static void DimensionsWarningOnly1D(int length, int width, int height)
    {
        if (width > 1 or height > 1)
        {
            BasicsInfo::Warning("One dimensional model is selected. ",
                                "Width and Height values are ignored!");
        }
    }

    static void DimensionsWarningOnly2D(int length, int width, int height)
    {
        if (width > 1 or height > 1)
        {
            BasicsInfo::Warning("Two dimensional model is selected. ",
                                "Height value is ignored!");
        }
    }
};

#endif