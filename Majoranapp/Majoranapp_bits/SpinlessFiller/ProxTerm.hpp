#ifndef SPINLESSFILLER_PROXTERM_HPP
#define SPINLESSFILLER_PROXTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"
#include "../SpinfullFiller/ProxTerm.hpp"

namespace Spinless
{

/**
 * @brief superconducting term
 * \f[
 * \hat H_{\mathrm{prox}} = 
 * \sum_{\langle i,j\rangle}
 * \left(\Delta_{ij}e^{i\phi_{ij}}
 * c_{i}^\dagger c_{j}+\mathrm{h.c.}\right) = 
 * i\sum_{\langle i,j\rangle}
 * \frac{\Delta_{ij}}{2}\left(
 * \sin \phi_{ij} \gamma_i^+ \gamma_j^+
 * +\cos \phi_{ij} \gamma_i^+ \gamma_j^-
 * -\cos \phi_{ij} \gamma_j^+ \gamma_i^-
 * -\sin \phi_{ij} \gamma_i^- \gamma_j^-
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
     * @param delta delta potential value \f$\Delta_{ij}\f$
     * @param i site index 
     * @param j site index
     * @param phase superconducting phase value \f$\phi_{ij}\f$
     */
    template <class T>
    static void Fill(Hamiltonian<T> &ham, double delta, int i, int j, double phase = 0.0)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpPlus, j, 0.5 * delta * std::sin(phase));
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, j, 0.5 * delta * std::cos(phase));
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::UpMinus, i, -0.5 * delta * std::cos(phase));
        ham.InsertBlock(Gamma::UpMinus, i, Gamma::UpMinus, j, -0.5 * delta * std::sin(phase));
    }
    
    static const std::string name;
    static constexpr size_t locality{2};
};

const std::string ProxTerm::name{Spinfull::ProxTerm::name};

}

#endif