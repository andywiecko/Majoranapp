#ifndef SPINFULLFILLER_IMAGKINETICTERM_HPP
#define SPINFULLFILLER_IMAGKINETICTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"

namespace Spinfull
{

/**
 * @brief kinetic term
 * \f[
 * \hat H_{\mathrm{kin}} = 
 * \sum_{\langle i,j\rangle}
 * \sum_\sigma\left(t_{ij}
 * c_{i\sigma}^\dagger c_{j\sigma}^\dagger+\mathrm{h.c.}\right) = 
 * -i\sum_{\langle i,j\rangle}
 * \sum_\sigma\frac{t_{ij}}{2}\left(
 * \gamma_{i\sigma}^+ \gamma_{j\sigma}^+ + \gamma_{j\sigma}^- \gamma_{i\sigma}^-
 * \right)
 * \f]
 * 
 */
class ImagKineticTerm
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
      ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpPlus, j, 0.5 * t_integral );
      ham.InsertBlock(Gamma::UpMinus, i, Gamma::UpMinus, j, 0.5 * t_integral );
      
      ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownPlus, j, 0.5 * t_integral );
      ham.InsertBlock(Gamma::DownMinus, i, Gamma::DownMinus, j, 0.5 * t_integral );
    }
    
    static const std::string name;
    static constexpr size_t locality{2};
};

const std::string ImagKineticTerm::name{"t_imag"};

}

#endif