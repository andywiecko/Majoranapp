#ifndef FACTORY_SPINLESSUNIFORMCHAIN_HPP
#define FACTORY_SPINLESSUNIFORMCHAIN_HPP

#include "../Hamiltonian.hpp"
#include "../Parameters.hpp"
#include "../Dimensions.hpp"
#include "../Filler.hpp"
#include "../Info.hpp"

/**
 * @brief Spinless uniform 1D chain with open boundary conditions
 * 
 * Dimensions:
 * - Length (L)
 * 
 * Parameters:
 * - Non-local terms:
 *      - Spinless::KineticTerm
 *      - Spinless::ProxTerm
 * - Local terms:
 *      - Spinless::ChemicalTerm
 */
class SpinlessUniformChain
{
public:
    template <class T>
    static Hamiltonian<T> Generate(Dimensions &dimensions, Parameters &parameters)
    {
        int deg = 2;
        double phase = 0.0;
        int L = dimensions.GetLength();

        // check width and height for warning
        int W = dimensions.GetWidth();
        int H = dimensions.GetHeight();
        Info::DimensionsWarningOnly1D(L,W,H);

        Hamiltonian<T> ham(L, deg);
        for (int i = 0; i < L - 1; i++)
        {
            Filler<Spinless::KineticTerm>::Fill(ham, parameters, i, i + 1);
            Filler<Spinless::ProxTerm>::Fill(ham, parameters, i, i + 1, phase);
        }
        for (int i = 0; i < L; i++)
        {
            Filler<Spinless::ChemicalTerm>::Fill(ham, parameters, i);
        }

        return ham;
    }
};

#endif