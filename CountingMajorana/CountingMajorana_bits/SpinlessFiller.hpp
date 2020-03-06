#ifndef SPINLESSFILLER_HPP
#define SPINLESSFILLER_HPP

#include "EnumGamma.hpp"
#include "Hamiltonian.hpp"

/**
 * @brief static class for spinless model term filler
 * 
 * Support:
 *  * kinetic term \f$t_{ij}\f$
 *  * proximity (superconducting) term \f$\Delta_{ij} \f$
 *  * chemical potential term \f$ \mu_i \f$
 */
class SpinlessFiller
{
public:
    /**
     * @brief kinetic term
     * \f[
     * \hat H_{\mathrm{kin}} = 
     * \sum_{\langle i,j\rangle}
     * \left(t_{ij}
     * c_{i}^\dagger c_{j}+\mathrm{h.c.}\right) = 
     * -i\sum_{\langle i,j\rangle}
     * \frac{t_{ij}}{2}\left(
     * \gamma_{i}^+ \gamma_{j}^- + \gamma_{j}^+ \gamma_{i}^-
     * \right)
     * \f]
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param i site index
     * @param j site index
     * @param t_integral hopping value \f$t_{ij}\f$
     */
    template <class T>
    static void KineticTerm(Hamiltonian<T> &ham, int i, int j, double t_integral)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, j, -0.5 * t_integral);
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::UpMinus, i, -0.5 * t_integral);
    }
    /**
     * @brief kinetic term
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
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param i site index
     * @param j site index
     * @param delta delta potential value \f$\Delta_{ij}\f$
     * @param phase superconducting phase value \f$\phi_{ij}\f$
     */
    template <class T>
    static void ProxTerm(Hamiltonian<T> &ham, int i, int j, double delta, double phase = 0.0)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpPlus, j, 0.5 * delta * std::sin(phase));
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, j, 0.5 * delta * std::cos(phase));
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::UpMinus, i, -0.5 * delta * std::cos(phase));
        ham.InsertBlock(Gamma::UpMinus, i, Gamma::UpMinus, j, -0.5 * delta * std::sin(phase));
    }
    /**
     * @brief chemical potential term
     * \f[
     * \hat H_{\mu} = 
     * \sum_{i}\mu_{i}
     * \hat n_{i} =
     * -i\sum_{i}
     * \frac{\mu_{i}}{2}
     * \gamma_{i}^+ \gamma_{i}^-
     * \f]
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param i site index 
     * @param mu chemical potential value \f$\mu_{i}\f$
     */
    template <class T>
    static void ChemicalTerm(Hamiltonian<T> &ham, int i, double mu)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, i, -0.5 * mu);
    }
};

#endif