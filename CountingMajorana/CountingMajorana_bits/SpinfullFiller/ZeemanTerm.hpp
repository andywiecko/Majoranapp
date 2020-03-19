#ifndef SPINFULLFILLER_ZEEMANTERM_HPP
#define SPINFULLFILLER_ZEEMANTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"

namespace Spinfull
{

/**
 * @brief Zeeman term
 * \f[
 * \hat H_{\mathrm{Zeeman}} = 
 * \sum_{i}V_{i}^Z\left(
 * \hat n_{i\uparrow} - \hat n_{i\downarrow}
 * \right) =
 * i\sum_{i}
 * \frac{V_{i}^Z}{2}\left(
 * - \gamma_{i\uparrow}^+ \gamma_{i\uparrow}^-
 * + \gamma_{i\downarrow}^+ \gamma_{i\downarrow}^-
 * \right)
 * \f]
 * 
 */
class ZeemanTerm
{
public:
    /**
     * @brief Filler
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param zeeman Zeeman potential value \f$V_{i}^Z\f$
     * @param i site index 
     */
    template <class T>
    static void Fill(Hamiltonian<T> &ham, double zeeman, int i)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, i, -0.5 * zeeman);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownMinus, i, +0.5 * zeeman);
    }
    static const std::string name;
};

const std::string ZeemanTerm::name{"zeeman"};

}

#endif