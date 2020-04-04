#ifndef SPINFULLFILLER_RASHBAYTERM_HPP
#define SPINFULLFILLER_RASHBAYTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"

namespace Spinfull
{

/**
 * @brief Rashba Y term
 * \f[
 * \hat H_{\mathrm{Rashba}\, y} = 
 * \sum_{\langle i,j\rangle}\sum_{\sigma\sigma'} \alpha_{ij}^y c_{i\sigma}^\dagger (i\sigma^y)_{\sigma\sigma'} c_{j\sigma'} +\mathrm{h.c.}= 
 * \sum_{\langle i,j\rangle}\alpha_{ij}^y\left(
 * c_{i\uparrow}^\dagger c_{j\downarrow}
 * -c_{i\downarrow}^\dagger c_{j\uparrow}\right)
 * +\mathrm{h.c.} = 
 * i\sum_{\langle i,j\rangle}
 * \frac{\alpha_{ij}^y}{2}\left(
 * -\gamma_{i\uparrow}^+ \gamma_{j\downarrow}^-
 * -\gamma_{j\downarrow}^+ \gamma_{i\uparrow}^-
 * +\gamma_{i\downarrow}^+ \gamma_{j\uparrow}^-
 * +\gamma_{j\uparrow}^+ \gamma_{i\downarrow}^-
 * \right)
 * \f]
 * 
 */
class RashbaYTerm
{
public:
    /** 
     * @brief Filler
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param rashbaY rashba interaction value \f$\alpha_{ij}^y\f$
     * @param i site index 
     * @param j site index 
     */
    template <class T>
    static void Fill(Hamiltonian<T> &ham, double rashbaY, int i, int j)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::DownMinus, j, -0.5 * rashbaY);
        ham.InsertBlock(Gamma::DownPlus, j, Gamma::UpMinus, i, -0.5 * rashbaY);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::UpMinus, j, +0.5 * rashbaY);
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::DownMinus, i, +0.5 * rashbaY);
    }
    static const std::string name;
    static constexpr size_t locality{2};
};

const std::string RashbaYTerm::name{"rashbaY"};

}

#endif