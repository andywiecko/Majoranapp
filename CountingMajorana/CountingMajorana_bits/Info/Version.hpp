#ifndef INFO_VERSION_HPP
#define INFO_VERSION_HPP

#include <armadillo>

#include "Basics.hpp"

class VersionInfo
{
    static const std::string libname;
    static const std::string vername;
    static const int major{0};
    static const int minor{150};
    static const int patch{0};

    static arma::arma_version armaVersion;

    static const nlohmann::basic_json<> jsonVer;
    static const std::string jsonVersion;

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
        std::cout << "# nlohmann JSON   " << " @ " << jsonVersion << "\n";
	    BasicsInfo::Line();
    }
};

const std::string VersionInfo::libname{"CountingMajorana"};
const std::string VersionInfo::vername{"alpha"};
const nlohmann::basic_json<> VersionInfo::jsonVer = nlohmann::json::meta();
const std::string VersionInfo::jsonVersion = VersionInfo::jsonVer["version"]["string"];

#endif