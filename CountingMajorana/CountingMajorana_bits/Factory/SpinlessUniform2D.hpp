#ifndef FACTORY_SPINLESSUNIFORMC2D_HPP
#define FACTORY_SPINLESSUNIFORMC2D_HPP

#include "../Hamiltonian.hpp"
#include "../QuantumSystem.hpp"
#include "../Filler.hpp"

#include "../VectorViewers/Grid2DViewer.hpp"

/**
 * @brief Spinless uniform 2D plaquette with open boundary conditions
 * 
 * Dimensions:
 * - Length (L)
 * - Width (W)
 * 
 * Parameters:
 * - Non-local terms:
 *      - Spinless::KineticTerm
 *      - Spinless::ProxTerm (phase in X: 0.0, phase in Y: -½π)
 * - Local terms:
 *      - Spinless::ChemicalTerm
 */
class SpinlessUniform2D : public Grid2DViewer
{
public:
    template <class T>
    static Hamiltonian<T> Generate(QuantumSystem &quantumSystem)
    {
        Dimensions &dimensions = quantumSystem.dimensions;
        Parameters &parameters = quantumSystem.parameters;

        int deg = 2;
        double phaseX = -0.5 * M_PI;
        double phaseY = 0.0;
        int length = dimensions.GetLength();
        int width = dimensions.GetWidth();
        int N = length * width;
        Hamiltonian<T> ham(N, deg);

        // local terms
        for (int i = 0; i < N; i++)
        {
            Filler<Spinless::ChemicalTerm>::Fill(ham, parameters, i);
        }

        // x-direction links
        for (int y = 0; y < width; y++)
        {
            for (int x = 0; x < length - 1; x++)
            {
                int from = y * length + x;
                int to = y * length + x + 1;
                //std::cout << "(" << from << ", " << to << ")" << std::endl;
                Filler<Spinless::KineticTerm>::Fill(ham, parameters, from, to);
                Filler<Spinless::ProxTerm>::Fill(ham, parameters, from, to, phaseX);
            }
        }

        //std::cout << std::endl;

        // y-direction links
        for (int x = 0; x < length; x++)
        {
            for (int y = 0; y < width - 1; y++)
            {
                int from = y * length + x;
                int to = (y + 1) * length + x;
                //std::cout << "(" << from << ", " << to << ")" << std::endl;
                Filler<Spinless::KineticTerm>::Fill(ham, parameters, from, to);
                Filler<Spinless::ProxTerm>::Fill(ham, parameters, from, to, phaseY);
            }
        }

        return ham;
    }
};

#endif