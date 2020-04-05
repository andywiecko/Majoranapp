#ifndef INFO_TIME_HPP
#define INFO_TIME_HPP

#include <armadillo>

class TimeInfo
{
private:
    static arma::wall_clock clock;

public:
    static void StartClock()
    {
        
        TimeInfo::clock.tic();
    }

    static double Time()
    {
        return TimeInfo::clock.toc();
    }
};

arma::wall_clock TimeInfo::clock{arma::wall_clock()};

#endif