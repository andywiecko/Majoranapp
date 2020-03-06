#ifndef ENUMGAMMA_HPP
#define ENUMGAMMA_HPP

/**
 * @brief enum class for gamma enumeration
 * 
 *  * \f$ \gamma_{i\sigma}^+ = c_{i\sigma}+c_{i\sigma}^\dagger \f$
 *  * \f$ \gamma_{i\sigma}^- = i(c_{i\sigma}-c_{i\sigma}^\dagger) \f$
 *
 */
enum class Gamma 
{
    //! \f$ \gamma_{\uparrow}^+ \f$
    UpPlus = 0, 
    //! \f$ \gamma_{\uparrow}^- \f$
    UpMinus = 1,
    //! \f$ \gamma_{\downarrow}^+ \f$
    DownPlus = 2,
    //! \f$ \gamma_{\downarrow}^- \f$
    DownMinus = 3
};

#endif