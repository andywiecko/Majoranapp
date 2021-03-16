#ifndef SPINLESSFILLER_REALPROXTERM_HPP
#define SPINLESSFILLER_REALPROXTERM_HPP

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
 * |\left(\Delta_{ij}|
 * c_{i}^\dagger c_{j}+\mathrm{h.c.}\right) = 
 * i\sum_{\langle i,j\rangle}
 * \frac{|\Delta_{ij}|}{2}\left(
 * \gamma_i^+ \gamma_j^- -
 * \gamma_j^+ \gamma_i^-
 * \right)
 * \f]
 * 
 */
class RealProxTerm
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
    static void Fill(Hamiltonian<T> &ham, double  delta, int i, int j)
    {

        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, j, 0.5 * delta);
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::UpMinus, i, -0.5 * delta);

    }
    
    static const std::string name;
    static constexpr size_t locality{2};
};

const std::string RealProxTerm::name{"delta_real"};

}

#endif