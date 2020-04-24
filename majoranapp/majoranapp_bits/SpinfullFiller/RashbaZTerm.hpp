#ifndef SPINFULLFILLER_RASHBAZTERM_HPP
#define SPINFULLFILLER_RASHBAZTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"

namespace Spinfull
{

/**
 * @brief Rashba Z term
 * \f[
 * \hat H_{\mathrm{Rashba}\, z} = 
 * \sum_{\langle i,j\rangle}\sum_{\sigma\sigma'} \alpha_{ij}^z c_{i\sigma}^\dagger (i\sigma^z)_{\sigma\sigma'} c_{j\sigma'} +\mathrm{h.c.}= 
 * \sum_{\langle i,j\rangle}\alpha_{ij}^z\left(
 * i c_{i\uparrow}^\dagger c_{j\uparrow}
 * -i c_{i\downarrow}^\dagger c_{j\downarrow}\right)
 * +\mathrm{h.c.} = 
 * i\sum_{\langle i,j\rangle}
 * \frac{\alpha_{ij}^z}{2}\left(
 * \gamma_{i\uparrow}^+ \gamma_{j\uparrow}^+
 * +\gamma_{i\uparrow}^- \gamma_{j\uparrow}^-
 * -\gamma_{i\downarrow}^+ \gamma_{j\downarrow}^+
 * -\gamma_{j\downarrow}^- \gamma_{i\downarrow}^-
 * \right)
 * \f]
 * 
 */
class RashbaZTerm
{
public:
    /** 
     * @brief Filler
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param rashbaY rashba interaction value \f$\alpha_{ij}^z\f$
     * @param i site index 
     * @param j site index 
     */
    template <class T>
    static void Fill(Hamiltonian<T> &ham, double rashbaZ, int i, int j)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpPlus, j, 0.5 * rashbaZ);
        ham.InsertBlock(Gamma::UpMinus, i, Gamma::UpMinus, j, 0.5 * rashbaZ);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownPlus, j, -0.5 * rashbaZ);
        ham.InsertBlock(Gamma::DownMinus, i, Gamma::DownMinus, j, -0.5 * rashbaZ);
    }
    
    static const std::string name;
    static constexpr size_t locality{2};
};

const std::string RashbaZTerm::name{"rashbaZ"};

}

#endif