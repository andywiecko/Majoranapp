#ifndef INFO_VERSION_HPP
#define INFO_VERSION_HPP

#include <armadillo>

#include "Basics.hpp"

/**
 * @brief Version of the lib and dependency libs
 */
class VersionInfo
{
private:
    static const std::string libname;
    static const std::string vername;
    static const int major{0};
    static const int minor{200};
    static const int patch{1};

    /**
     * @brief armadillo version
     */
    static arma::arma_version armaVersion;

    static const nlohmann::basic_json<> jsonVer;

    /**
     * @brief nlohmann::json version
     */
    static const std::string jsonVersion;

    /**
     * @brief returns lib version
     * 
     * @return std::string 
     */
    static std::string Version()
    {
        return std::to_string(major) + "." +
               std::to_string(minor) + "." +
               std::to_string(patch);
    }

public:
    /**
     * @brief displays all libs version
     */
    static void ShowVersion()
    {
        // TODO set width depending on max lib name
        std::cout << "# " << libname << "       @ " << Version() << " (" << vername << ")\n";
        std::cout << "# armadillo       "
                  << " @ " << armaVersion.as_string() << "\n";
        std::cout << "# nlohmann JSON   "
                  << " @ " << jsonVersion << "\n";
        BasicsInfo::Line();
    }
};

const std::string VersionInfo::libname{"Majoranapp"};
const std::string VersionInfo::vername{"alpha"};
const nlohmann::basic_json<> VersionInfo::jsonVer = nlohmann::json::meta();
const std::string VersionInfo::jsonVersion = VersionInfo::jsonVer["version"]["string"];

#endif