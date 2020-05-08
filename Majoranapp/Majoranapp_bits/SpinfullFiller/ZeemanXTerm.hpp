#ifndef SPINFULLFILLER_ZEEMANXTERM_HPP
#define SPINFULLFILLER_ZEEMANXTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"

namespace Spinfull
{

/**
 * @brief Zeeman in X (spin flip) term 
 * \f[
 * \hat H_{\mathrm{Zeeman}\, x} = 
 * \sum_{i} \sum_{\sigma\sigma'} V_{i}^X c_{i\sigma}^\dagger (\sigma^x)_{\sigma\sigma'} c_{i\sigma'} = 
 * \sum_{i}V_{i}^X\left(
 * c_{i\uparrow}^\dagger c_{i\downarrow}
 * +\mathrm{h.c.}\right)=
 * -i\sum_{i}
 * \frac{V_{i}^X}{2}\left(
 * \gamma_{i\uparrow}^+\gamma_{i\downarrow}^-
 * +\gamma_{i\downarrow}^+ \gamma_{i\uparrow}^-
 * \right)
 * \f]
 *
 */
class ZeemanXTerm
{
public:
    /**
     * @brief Filler
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param delta delta potential value \f$\Delta_{i}\f$
     * @param i site index 
     */
    template <class T>
    static void Fill(Hamiltonian<T> &ham, double flip, int i)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::DownMinus, i, -0.5 * flip);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::UpMinus, i, -0.5 * flip);
    }
    
    static const std::string name;
    static constexpr size_t locality{1};
};

const std::string ZeemanXTerm::name{"zeemanX"};

}

#endif