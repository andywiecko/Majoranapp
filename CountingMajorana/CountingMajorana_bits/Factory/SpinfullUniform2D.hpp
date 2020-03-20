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
        int length = dimensions.map[Dimensions::lengthName]; // TODO make it more elegant
        int height = dimensions.map[Dimensions::heightName];
        int N = length * height;

        Hamiltonian<T> ham(N, deg);

        // local terms
        for (int i = 0; i < N; i++)
        {
            Filler<Spinfull::ProxTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ZeemanTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::ChemicalTerm>::Fill(ham, parameters, i);
            Filler<Spinfull::SpinFlipTerm>::Fill(ham, parameters, i);
        }

        // x-direction links
        for (int y = 0; y < height; y++)
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
            for (int y = 0; y < height-1; y++)
            {
                int from = y * length + x;
                int to = (y+1) * length + x;
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