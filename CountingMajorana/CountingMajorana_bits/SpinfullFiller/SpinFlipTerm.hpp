#ifndef SPINFULLFILLER_SPINFLIPTERM_HPP
#define SPINFULLFILLER_SPINFLIPTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"

namespace Spinfull
{

/**
 * @brief proximity term
 * \f[
 * \hat H_{\mathrm{flip}} = 
 * \sum_{i}f_{i}\left(
 * c_{i\uparrow}^\dagger c_{i\downarrow}
 * +\mathrm{h.c.}\right)=
 * -i\sum_{i}
 * \frac{f_{i}}{2}\left(
 * \gamma_{i\uparrow}^+\gamma_{i\downarrow}^-
 * +\gamma_{i\downarrow}^+ \gamma_{i\uparrow}^-
 * \right)
 * \f]
 *
 */
class SpinFlipTerm
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
};

const std::string SpinFlipTerm::name{"spin_flip"};

}

#endif