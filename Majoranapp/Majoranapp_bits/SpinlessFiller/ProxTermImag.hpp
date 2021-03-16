#ifndef SPINLESSFILLER_IMAGPROXTERM_HPP
#define SPINLESSFILLER_IMAGPROXTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"
#include <complex>
namespace Spinless
{

/**
 * @brief complex superconducting term
 * \f[
 * \hat H_{\mathrm{prox}} = 
 * \sum_{\langle i,j\rangle}
 * \left(|\Delta_{ij}|\exp(i\pi/2)
 * c_{i}^\dagger c_{j}+\mathrm{h.c.}\right) = 
 * i\sum_{\langle i,j\rangle}
 * \frac{|\Delta_{ij}|}{2}\left(
 *  \gamma_i^+ \gamma_j^+ -
 *  \gamma_i^- \gamma_j^-
 * \right)
 * \f]
 * 
 */
class ImagProxTerm
{
public:
    /**
     * @brief Filler
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param delta delta (complex number) potential value \f$\Delta_{ij}\f$
     * @param i site index 
     * @param j site index
     */
    template <class T>
    static void Fill(Hamiltonian<T> &ham, double delta, int i, int j)
    {

        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpPlus, j, 0.5 * delta );
        ham.InsertBlock(Gamma::UpMinus, i, Gamma::UpMinus, j, -0.5 * delta );
    }
    
    static const std::string name;
    static constexpr size_t locality{2};
};

const std::string ImagProxTerm::name{"delta_imag"};

}

#endif