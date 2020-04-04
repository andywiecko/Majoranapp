#ifndef SPINFULLFILLER_PROXTERM_HPP
#define SPINFULLFILLER_PROXTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"

namespace Spinfull
{

/**
 * @brief proximity term
 * \f[
 * \hat H_{\mathrm{prox}} = 
 * \sum_{i}\Delta_{i}\left(
 * c_{i\uparrow}^\dagger c_{i\downarrow}^\dagger
 * +\mathrm{h.c.}\right)=
 * i\sum_{i}
 * \frac{\Delta_{i}}{2}\left(
 * +\gamma_{i\uparrow}^+\gamma_{i\downarrow}^-
 * -\gamma_{i\downarrow}^+ \gamma_{i\uparrow}^-
 * \right)
 * \f]
 *
 */
class ProxTerm
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
    static void Fill(Hamiltonian<T> &ham, double delta, int i)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::DownMinus, i, +0.5 * delta);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::UpMinus, i, -0.5 * delta);
    }
    static const std::string name;
    static constexpr size_t locality{1};
};

const std::string ProxTerm::name{"delta"};

}

#endif