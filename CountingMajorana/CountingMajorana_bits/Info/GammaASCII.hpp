#ifndef INFO_GAMMAASCII_HPP
#define INFO_GAMMAASCII_HPP

#include <string>

class GammaASCII
{
private:
    static const std::string gamma;
    static const std::string up;
    static const std::string down;

public:
    static std::string GammaUp()
    {
        return gamma+up;
    }

    static std::string GammaDown()
    {
        return gamma+down;
    }

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