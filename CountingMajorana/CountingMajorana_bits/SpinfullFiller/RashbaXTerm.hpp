#ifndef SPINFULLFILLER_RASHBAXTERM_HPP
#define SPINFULLFILLER_RASHBAXTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"

namespace Spinfull
{

/**
 * @brief Rashba X term
 * \f[
 * \hat H_{\mathrm{Rashba}\, x} = 
 * \sum_{\langle i,j\rangle}\sum_{\sigma\sigma'} \alpha_{ij}^x c_{i\sigma}^\dagger (i\sigma^x)_{\sigma\sigma'} c_{j\sigma'} +\mathrm{h.c.}= 
 * \sum_{\langle i,j\rangle} i\alpha_{ij}^x \left(
 *  c_{i\uparrow}^\dagger c_{j\downarrow}
 * +c_{i\downarrow}^\dagger c_{j\uparrow}\right)
 * +\mathrm{h.c.} = 
 * i\sum_{\langle i,j\rangle}
 * \frac{\alpha_{ij}^x}{2}\left(
 * \gamma_{i\uparrow}^+ \gamma_{j\downarrow}^+
 * +\gamma_{j\downarrow}^- \gamma_{i\uparrow}^-
 * +\gamma_{i\downarrow}^+ \gamma_{j\uparrow}^+
 * +\gamma_{j\uparrow}^- \gamma_{i\downarrow}^-
 * \right)
 * \f]
 * 
 */
class RashbaXTerm
{
public:
    /**
     * @brief Filler
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param rashbaX rashba interaction value \f$\alpha_{ij}^x\f$
     * @param i site index 
     * @param j site index 
     */
    template <class T>
    static void Fill(Hamiltonian<T> &ham, double rashbaX, int i, int j)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::DownPlus, j, +0.5 * rashbaX);
        ham.InsertBlock(Gamma::UpMinus, i, Gamma::DownMinus, j, +0.5 * rashbaX);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::UpPlus, j, +0.5 * rashbaX);
        ham.InsertBlock(Gamma::DownMinus, i, Gamma::UpMinus, j, +0.5 * rashbaX);
    }
    static const std::string name;
    static constexpr size_t locality{2};
};

const std::string RashbaXTerm::name{"rashbaX"};

}

#endif