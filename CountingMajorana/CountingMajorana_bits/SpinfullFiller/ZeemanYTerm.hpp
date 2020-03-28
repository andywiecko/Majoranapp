#ifndef SPINFULLFILLER_ZEEMANYTERM_HPP
#define SPINFULLFILLER_ZEEMANYTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"

namespace Spinfull
{

/**
 * @brief Zeeman in Y term 
 * \f[
 * \hat H_{\mathrm{Zeeman}\, y} = 
 * \sum_{i} \sum_{\sigma\sigma'} V_{i}^Y c_{i\sigma}^\dagger (\sigma^y)_{\sigma\sigma'} c_{i\sigma'} = 
 * \sum_{i}V_{i}^Y\left(
 * ic_{i\uparrow}^\dagger c_{i\downarrow}
 * +\mathrm{h.c.}\right)=
 * i\sum_{i}
 * \frac{V_{i}^Y}{2}\left(
 * \gamma_{i\uparrow}^+\gamma_{i\downarrow}^+
 * +\gamma_{i\uparrow}^- \gamma_{i\downarrow}^-
 * \right)
 * \f]
 *
 */
class ZeemanYTerm
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
    static void Fill(Hamiltonian<T> &ham, double zeemany, int i)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::DownPlus, i, 0.5 * zeemany);
        ham.InsertBlock(Gamma::UpMinus, i, Gamma::DownMinus, i, 0.5 * zeemany);
    }
    static const std::string name;
};

const std::string ZeemanYTerm::name{"zeemany"};

}

#endif