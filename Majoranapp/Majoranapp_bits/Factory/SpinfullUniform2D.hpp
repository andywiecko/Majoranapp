#ifndef FACTORY_SPINFULLUNIFORM2D_HPP
#define FACTORY_SPINFULLUNIFORM2D_HPP

#include "../Hamiltonian.hpp"
#include "../QuantumSystem.hpp"
#include "../Filler.hpp"
#include "../Info.hpp"
#include "../VectorViewers/Grid2DViewer.hpp"

#include "../ConnectionsFiller.hpp"

/**
 * @brief Spinfull 2D plaquette with open boundary conditions
 * 
 * Dimensions:
 * - Length (L)
 * - Width (W)
 * 
 * Parameters:
 * - Non-local terms:
 *      - Spinfull::KineticTerm
 *      - Spinfull::RashbaXTerm
 *      - Spinfull::RashbaYTerm
 * - Local terms:
 *      - Spinfull::ProxTerm
 *      - Spinfull::ChemicalTerm
 *      - Spinfull::ZeemanXTerm
 *      - Spinfull::ZeemanZTerm
 */
class SpinfullUniform2D : public Grid2DViewer
{
public:
    template <class T>
    static Hamiltonian<T> Generate(QuantumSystem &quantumSystem)
    {
        Dimensions &dimensions = quantumSystem.dimensions;
        Parameters &parameters = quantumSystem.parameters;

        int deg = 4;
        int length = dimensions.GetLength();
        int width = dimensions.GetWidth();

        // check height for warning
        int height = dimensions.GetHeight();
        Info::DimensionsWarningOnly2D(length, width, height);

        int N = length * width;

        Hamiltonian<T> ham(N, deg);

        // local terms
        for (int i = 0; i < N; i++)
        {
            Filler<Spinfull::ProxTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ZeemanXTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ZeemanYTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ZeemanZTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ChemicalTerm>::Fill(ham, parameters, i);
        }

        // x-direction links
        for (int y = 0; y < width; y++)
        {
            for (int x = 0; x < length - 1; x++)
            {
                int from = y * length + x;
                int to = y * length + x + 1;
                //std::cout << "(" << from << ", " << to << ")" << std::endl;
                Filler<Spinfull::KineticTerm>::Fill(ham, parameters, from, to);
                //Filler<Spinfull::RashbaXTerm>::Fill(ham, parameters, from, to);
                Filler<Spinfull::RashbaYTerm>::Fill(ham, parameters, from, to);
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
                Filler<Spinfull::KineticTerm>::Fill(ham, parameters, from, to);
                Filler<Spinfull::RashbaXTerm>::Fill(ham, parameters, from, to);
                //Filler<Spinfull::RashbaYTerm>::Fill(ham, parameters, from, to);
            }
        }

        return ham;
    }
};

#endif