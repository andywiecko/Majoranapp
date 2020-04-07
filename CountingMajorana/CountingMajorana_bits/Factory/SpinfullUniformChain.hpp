#ifndef FACTORY_SPINFULLUNIFORMCHAIN_HPP
#define FACTORY_SPINFULLUNIFORMCHAIN_HPP

#include "../Hamiltonian.hpp"
#include "../QuantumSystem.hpp"
#include "../Filler.hpp"
#include "../Info.hpp"

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
 *      - Spinfull::ZeemanZTerm
 *      - Spinfull::ChemicalTerm
 */
class SpinfullUniformChain
{
public:
    template <class T>
    static Hamiltonian<T> Generate(QuantumSystem &quantumSystem)
    {
        Dimensions &dimensions = quantumSystem.dimensions;
        Parameters &parameters = quantumSystem.parameters;

        int deg = 4;
        int L = dimensions.GetLength();

        // check width and height for warning
        int W = dimensions.GetWidth();
        int H = dimensions.GetHeight();
        Info::DimensionsWarningOnly1D(L,W,H);

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
            Filler<Spinfull::ZeemanZTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ChemicalTerm>::Fill(ham, parameters, i);
        }

        return ham;
    }
};

#endif