#ifndef INFO_TIME_HPP
#define INFO_TIME_HPP

#include <armadillo>

/**
 * @brief clock for time measurement
 */
class TimeInfo
{
private:
    /**
     * @brief clock object
     */
    static arma::wall_clock clock;

public:
    /**
     * @brief stats time measurement
     */
    static void StartClock()
    {
        
        TimeInfo::clock.tic();
    }

    /**
     * @brief returns current clock time (in seconds)
     * 
     * @return double (seconds)
     */
    static double Time()
    {
        return TimeInfo::clock.toc();
    }
};

arma::wall_clock TimeInfo::clock{arma::wall_clock()};

#endif