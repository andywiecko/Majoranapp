#ifndef INFO_GAMMAASCII_HPP
#define INFO_GAMMAASCII_HPP

#include <string>

/**
 * @brief Some ASCII art decorators
 */
class GammaASCII
{
private:
    /**
     * @brief gamma greek letter
     */
    static const std::string gamma;
    /**
     * @brief ASCII arrow up
     */
    static const std::string up;
    /**
     * @brief ASCII arrow down
     */
    static const std::string down;

public:
    /**
     * @brief returns ASCII gamma greek letter and arrow up
     * 
     * @return std::string 
     */
    static std::string GammaUp()
    {
        return gamma+up;
    }

    /**
     * @brief returns ASCII gamma greek letter and arrow down
     * 
     * @return std::string 
     */
    static std::string GammaDown()
    {
        return gamma+down;
    }

    /**
     * @brief selects gamma of a given degree deg
     * 
     * @param deg degree 
     * @return std::string 
     */
    static std::string Gamma(int deg)
    {
        switch (deg)
        {
            case 0:
                return GammaUp();
                break;
            case 1:
                return GammaDown();
                break;
            default:
                return "?";
        }
    }

};

const std::string GammaASCII::gamma{"γ"};
const std::string GammaASCII::up{"↑"};
const std::string GammaASCII::down{"↓"};

#endif