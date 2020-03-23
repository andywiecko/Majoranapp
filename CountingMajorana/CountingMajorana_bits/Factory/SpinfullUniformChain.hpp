#ifndef FACTORY_SPINFULLUNIFORMCHAIN_HPP
#define FACTORY_SPINFULLUNIFORMCHAIN_HPP

#include "../Hamiltonian.hpp"
#include "../Parameters.hpp"
#include "../Dimensions.hpp"
#include "../Filler.hpp"

/**
 * @brief Spinfull uniform 1D chain with open boundary conditions
 * 
 * Dimensions:
 * - Length (L)
 * 
 * Parameters:
 * - Non-local terms:
 *      - Spinfull::KineticTerm
 *      - Spinfull::RashbaXTerm
 *      - Spinfull::RashbaYTerm
 * - Local terms:
 *      - Spinfull::ProxTerm
 *      - Spinfull::ZeemanTerm
 *      - Spinfull::ChemicalTerm
 */
class SpinfullUniformChain
{
public:
    template <class T>
    static Hamiltonian<T> Generate(Dimensions &dimensions, Parameters &parameters)
    {
        int deg = 4;
        int L = dimensions.GetLength();
        Hamiltonian<T> ham(L, deg);
        for (int i = 0; i < L - 1; i++)
        {
            Filler<Spinfull::KineticTerm>::Fill(ham, parameters, i, i + 1);
            Filler<Spinfull::RashbaXTerm>::Fill(ham, parameters, i, i + 1);
            Filler<Spinfull::RashbaYTerm>::Fill(ham, parameters, i, i + 1);
        }
        for (int i = 0; i < L; i++)
        {
            Filler<Spinfull::ProxTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ZeemanTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ChemicalTerm>::Fill(ham, parameters, i);
        }

        return ham;
    }
};

#endif