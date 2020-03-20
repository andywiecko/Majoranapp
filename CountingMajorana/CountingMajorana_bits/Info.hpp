#ifndef INFO_HPP
#define INFO_HPP

#include "Info/Basics.hpp"
#include "Info/ShowMap.hpp"
#include "Info/GammaASCII.hpp"

class Info : 
    public BasicsInfo,
    public ShowMapInfo,
    public GammaASCII
{

};

#endif