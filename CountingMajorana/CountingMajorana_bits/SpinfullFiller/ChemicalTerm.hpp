#ifndef SPINFULLFILLER_CHEMICALTERM_HPP
#define SPINFULLFILLER_CHEMICALTERM_HPP

#include "../Hamiltonian.hpp"
#include "../EnumGamma.hpp"

namespace Spinfull
{

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
 */
class ChemicalTerm
{
public:
    /**
     * @brief Filler
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param ham hamiltonian container
     * @param i site index 
     * @param mu chemical potential value \f$\mu_{i}\f$
     */
    template <class T>
    static void Fill(Hamiltonian<T> &ham, double mu, int i)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, i, -0.5 * mu);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownMinus, i, -0.5 * mu);
    }
    static const std::string name;
};

const std::string ChemicalTerm::name{"zeeman"};

}

#endif