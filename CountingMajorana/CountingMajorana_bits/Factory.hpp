#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Hamiltonian.hpp"
#include "Parameters.hpp"

// implemented geometries and stuff
#include "Factory/SpinfullUniformChain.hpp"
#include "Factory/SpinlessUniformChain.hpp"

/**
 * @brief class which produses stuff
 * 
 * @tparam O static object to execute
 */
template <class O>
class Factory
{
public:

    /**
     * @brief run the `Generate()` function of static class `O`
     * 
     * @tparam T matrix type, support for: arma::mat, arma::sp_mat
     * @param L number of sites
     * @param parameters parameters of the model
     * @return Hamiltonian<T> 
     */
    template <class T>
    static Hamiltonian<T> Generate(int &L, Parameters &parameters)
    {
        return O::template Generate<T>(L, parameters);
    }
};

#endif