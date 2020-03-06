#ifndef SPINFULLFILLER_HPP
#define SPINFULLFILLER_HPP

#include "EnumGamma.hpp"
#include "Hamiltonian.hpp"

/**
 * @brief static class for spinfull model term filler
 * 
 * Support:
 *  * kinetic term
 *  * Rashba term
 *  * proximity (superconducting) term
 *  * Zeeman term
 *  * chemical potential term
 */
class SpinfullFiller
{

private:
    static void DegreeWarning()
    {
        // TODO
    }

public:
    /**
     * @brief kinetic term
     * \f[
     * \hat H_{\mathrm{kin}} = 
     * \sum_{\langle i,j\rangle}
     * \sum_\sigma\left(t_{ij}
     * c_{i\sigma}^\dagger c_{j\sigma}+\mathrm{h.c.}\right) = 
     * -i\sum_{\langle i,j\rangle}
     * \sum_\sigma\frac{t_{ij}}{2}\left(
     * \gamma_{i\sigma}^+ \gamma_{j\sigma}^- + \gamma_{j\sigma}^+ \gamma_{i\sigma}^-
     * \right)
     * \f]
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param i site index 
     * @param j site index 
     * @param t_integral hopping value \f(t_{ij}\f)
     */
    template <class T>
    static void KineticTerm(Hamiltonian<T> &ham, int i, int j, double t_integral)
    {
        DegreeWarning();
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, j, -0.5 * t_integral);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownMinus, j, -0.5 * t_integral);
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::UpMinus, i, -0.5 * t_integral);
        ham.InsertBlock(Gamma::DownPlus, j, Gamma::DownMinus, i, -0.5 * t_integral);
    }
    /**
     * @brief rashba term
     * \f[
     * \hat H_{\mathrm{Rashba}} = 
     * \sum_{\langle i,j\rangle}\alpha_{ij}\left(
     * c_{i\uparrow}^\dagger c_{j\downarrow}
     * -c_{i\downarrow}^\dagger c_{j\uparrow}\right)
     * +\mathrm{h.c.} = 
     * i\sum_{\langle i,j\rangle}
     * \frac{\alpha_{ij}}{2}\left(
     * -\gamma_{i\uparrow}^+ \gamma_{j\downarrow}^-
     * -\gamma_{j\downarrow}^+ \gamma_{i\uparrow}^-
     * +\gamma_{i\downarrow}^+ \gamma_{j\uparrow}^-
     * +\gamma_{j\uparrow}^+ \gamma_{i\downarrow}^-
     * \right)
     * \f]
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param i site index 
     * @param j site index 
     * @param rashba rashba interaction value \f(\alpha_{ij}\f)
     */
    template <class T>
    static void RashbaTerm(Hamiltonian<T> &ham, int i, int j, double rashba)
    {
        DegreeWarning();
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::DownMinus, j, -0.5 * rashba);
        ham.InsertBlock(Gamma::DownPlus, j, Gamma::UpMinus, i, -0.5 * rashba);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::UpMinus, j, +0.5 * rashba);
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::DownMinus, i, +0.5 * rashba);
    }
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
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param i site index 
     * @param delta delta potential value \f(\Delta_{i}\f)
     */
   template <class T>
    static void ProxTerm(Hamiltonian<T> &ham, int i, double delta)
    {
        DegreeWarning();
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::DownMinus, i, +0.5 * delta);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::UpMinus, i, -0.5 * delta);
    }
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
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param i site index 
     * @param zeeman Zeeman potential value \f(V_{i}^Z\f)
     */
    template <class T>
    static void ZeemanTerm(Hamiltonian<T> &ham, int i, double zeeman)
    {
        DegreeWarning();
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, i, -0.5 * zeeman);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownMinus, i, +0.5 * zeeman);
    }
    /**
     * @brief chemical potential term
     * \f[
     * \hat H_{\mu} = 
     * \sum_{i\sigma}\mu_{i}
     * \hat n_{i\sigma} =
     * -i\sum_{i\sigma}
     * \frac{\mu_{i}}{2}
     * \gamma_{i\sigma}^+ \gamma_{i\sigma}^-
     * \f]
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param i site index 
     * @param zeeman Zeeman potential value \f(\mu_{i}\f)
     */
    template <class T>
    static void ChemicalTerm(Hamiltonian<T> &ham, int i, double mu)
    {
        DegreeWarning();
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, i, -0.5 * mu);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownMinus, i, -0.5 * mu);
    }
};

#endif