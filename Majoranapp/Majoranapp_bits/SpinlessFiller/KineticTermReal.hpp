#ifndef SPINLESSFILLER_REALKINETICTERM_HPP
#define SPINLESSFILLER_REALKINETICTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"
#include "../SpinfullFiller/KineticTerm.hpp"


namespace Spinless
{

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
 */
class RealKineticTerm
{
public:
    /**
     * @brief Filler
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param t_integral hopping value \f$t_{ij}\f$
     * @param i site index 
     * @param j site index 
     */
    template <class T>
    static void Fill(Hamiltonian<T> &ham, double t_integral,int i, int j)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, j, -0.5 * t_integral);
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::UpMinus, i, -0.5 * t_integral);
    }
    
    static const std::string name;
    static constexpr size_t locality{2};
};

const std::string RealKineticTerm::name{"t_real"};

}

#endif