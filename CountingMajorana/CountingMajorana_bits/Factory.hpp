#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Hamiltonian.hpp"
#include "Parameters.hpp"
#include "Dimensions.hpp"

// implemented geometries and stuff
#include "Factory/SpinlessUniformChain.hpp"
#include "Factory/SpinfullUniformChain.hpp"
#include "Factory/SpinfullUniform2D.hpp"
#include "Factory/SpinfullUniform3D.hpp"

/**
 * @brief class which produces stuff
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
     * @param dimensions dimensions of the model
     * @param parameters parameters of the model
     * @return Hamiltonian<T> 
     */
    template <class T,typename ... Targs>
    static Hamiltonian<T> Generate(Dimensions &dimensions, Parameters &parameters, Targs... Fargs)
    {
        return O::template Generate<T>(dimensions, parameters, Fargs...);
    }
};

#endif