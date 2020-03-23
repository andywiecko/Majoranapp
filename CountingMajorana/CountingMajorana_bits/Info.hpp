#ifndef INFO_HPP
#define INFO_HPP

#include "Info/Basics.hpp"
#include "Info/ShowMap.hpp"
#include "Info/GammaASCII.hpp"
#include "Info/Version.hpp"
#include "Info/Colors.hpp"

/**
 * @brief misc class containing all stuff related with cout
 */
class Info : 
    public BasicsInfo,
    public ShowMapInfo,
    public GammaASCII,
    public VersionInfo,
    public ColorsInfo
{

};

#endif