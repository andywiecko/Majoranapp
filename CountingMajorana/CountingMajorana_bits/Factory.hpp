#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Hamiltonian.hpp"
#include "QuantumSystem.hpp"
#include "QuantumSystem/Parameters.hpp"
#include "QuantumSystem/Dimensions.hpp"

// implemented geometries and stuff
// - Spinless
#include "Factory/SpinlessUniformChain.hpp"
#include "Factory/SpinlessUniform2D.hpp"
// - Spinfull
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
    static Hamiltonian<T> Generate(QuantumSystem &quantumSystem, Targs... Fargs)
    {
        return O::template Generate<T>(quantumSystem, Fargs...);
    }
};

#endif