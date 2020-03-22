#ifndef INFO_VERSION_HPP
#define INFO_VERSION_HPP

#include <armadillo>

#include "Basics.hpp"

class VersionInfo
{
    static const std::string libname;
    static const std::string vername;
    static const int major{0};
    static const int minor{100};
    static const int patch{0};

    static arma::arma_version armaVersion;

    static std::string Version()
    {
        return std::to_string(major) + "." +
               std::to_string(minor) + "." +
               std::to_string(patch);
    }

public:
    static void ShowVersion()
    {
        std::cout << "# " << libname << " @ " << Version() << " (" << vername << ")\n";
        std::cout << "# armadillo       " << " @ " << armaVersion.as_string() << "\n";
        BasicsInfo::Line();
    }
};

const std::string VersionInfo::libname{"CountingMajorana"};
const std::string VersionInfo::vername{"alpha"};

#endif