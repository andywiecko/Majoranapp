#ifndef FACTORY_SPINFULLUNIFORM2D_HPP
#define FACTORY_SPINFULLUNIFORM2D_HPP

#include "../Hamiltonian.hpp"
#include "../Parameters.hpp"
#include "../Dimensions.hpp"
#include "../Filler.hpp"

class SpinfullUniform2D
{
public:
    template <class T>
    static Hamiltonian<T> Generate(Dimensions &dimensions, Parameters &parameters)
    {
        int deg = 4;
        int length = dimensions.map["Length"];
        int height = dimensions.map["Height"];
        int N = length * height;

        Hamiltonian<T> ham(N, deg);

        // local terms
        for (int i = 0; i < N; i++)
        {
            Filler<Spinfull::ProxTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ZeemanTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ChemicalTerm>::Fill(ham, parameters, i);
        }

        for (int x = 0; x < length - 1; x++)
        {
            for (int y = 0; y < height - 1; y++)
            {
                Filler<Spinfull::KineticTerm>::Fill(ham, parameters, x, y);
                Filler<Spinfull::RashbaXTerm>::Fill(ham, parameters, x, y);
                Filler<Spinfull::RashbaYTerm>::Fill(ham, parameters, x, y);
            }
        }

        return ham;
    }
};

#endif