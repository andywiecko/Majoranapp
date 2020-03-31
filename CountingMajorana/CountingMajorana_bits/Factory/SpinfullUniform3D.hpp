#ifndef FACTORY_SPINFULLUNIFORM3D_HPP
#define FACTORY_SPINFULLUNIFORM3D_HPP

#include "../Hamiltonian.hpp"
#include "../Parameters.hpp"
#include "../Dimensions.hpp"
#include "../Filler.hpp"
#include "../VectorViewers/Grid3DViewer.hpp"

/**
 * @brief Spinfull 3D cuboid with open boundary conditions
 * 
 * Dimensions:
 * - Length (L)
 * - Width  (W)
 * - Height (H)
 * 
 * Parameters:
 * - Non-local terms:
 *      - Spinfull::KineticTerm
 *      - Spinfull::RashbaXTerm
 *      - Spinfull::RashbaYTerm
 *      - Spinfull::RashbaZTerm
 * - Local terms:
 *      - Spinfull::ProxTerm
 *      - Spinfull::ChemicalTerm
 *      - Spinfull::ZeemanXTerm
 *      - Spinfull::ZeemanYTerm
 *      - Spinfull::ZeemanZTerm
 */
class SpinfullUniform3D : public Grid3DViewer
{
public:
    template <class T>
    static Hamiltonian<T> Generate(Dimensions &dimensions, Parameters &parameters)
    {
        int deg = 4;
        int length = dimensions.GetLength();
        int width = dimensions.GetWidth();
        int height = dimensions.GetHeight();
        int N = length * width * height;

        Hamiltonian<T> ham(N, deg);

        // local terms
        for (int i = 0; i < N; i++)
        {
            Filler<Spinfull::ChemicalTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ProxTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ZeemanXTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ZeemanYTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ZeemanZTerm>::Fill(ham, parameters, i);
        }

        // x-direction links
        for (int z = 0; z < height; z++)
        {
            for (int y = 0; y < width; y++)
            {
                for (int x = 0; x < length - 1; x++)
                {
                    int from = ToSite(x, y, z, length, width);
                    int to = ToSite(x + 1, y, z, length, width);
                    //std::cout << "(" << from << ", " << to << ")" << std::endl;
                    Filler<Spinfull::KineticTerm>::Fill(ham, parameters, from, to);
                    Filler<Spinfull::RashbaYTerm>::Fill(ham, parameters, from, to);
                }
            }
        }

        //std::cout << std::endl;

        // y-direction links
        for (int z = 0; z < height; z++)
        {
            for (int x = 0; x < length; x++)
            {
                for (int y = 0; y < width - 1; y++)
                {
                    int from = ToSite(x, y, z, length, width);
                    int to = ToSite(x, y + 1, z, length, width);
                    //std::cout << "(" << from << ", " << to << ")" << std::endl;
                    Filler<Spinfull::KineticTerm>::Fill(ham, parameters, from, to);
                    Filler<Spinfull::RashbaXTerm>::Fill(ham, parameters, from, to);
                }
            }
        }

        // z-direction links
        for (int y = 0; y < width; y++)
        {
            for (int x = 0; x < length; x++)
            {
                for (int z = 0; z < height - 1; z++)
                {
                    int from = ToSite(x, y, z, length, width);
                    int to = ToSite(x, y, z + 1, length, width);
                    //std::cout << "(" << from << ", " << to << ")" << std::endl;
                    Filler<Spinfull::KineticTerm>::Fill(ham, parameters, from, to);
                    Filler<Spinfull::RashbaZTerm>::Fill(ham, parameters, from, to);
                }
            }
        }

        return ham;
    }

private:
    static int ToSite(int x, int y, int z, int L, int W)
    {
        return x + L * y + L * W * z;
    }
};

#endif