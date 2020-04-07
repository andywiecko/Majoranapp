#ifndef INFO_HPP
#define INFO_HPP

#include "Info/Basics.hpp"
#include "Info/ShowMap.hpp"
#include "Info/GammaASCII.hpp"
#include "Info/Version.hpp"
#include "Info/Colors.hpp"
#include "Info/DimensionsWarning.hpp"
#include "Info/Time.hpp"

/**
 * @brief misc class containing all stuff related with cout, clog
 */
class Info : 
    public BasicsInfo,
    public ShowMapInfo,
    public GammaASCII,
    public VersionInfo,
    public ColorsInfo,
    public DimensionsWarningInfo,
    public TimeInfo
{

};



#endif