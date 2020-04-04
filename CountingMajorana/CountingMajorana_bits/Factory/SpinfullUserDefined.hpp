#ifndef FACTORY_SPINFULLUSERDEFINED_HPP
#define FACTORY_SPINFULLUSERDEFINED_HPP

#include "../Hamiltonian.hpp"
#include "../QuantumSystem.hpp"
#include "../Filler.hpp"
#include "../Info.hpp"
#include "../ConnectionsFiller.hpp"

class SpinfullUserDefined
{
    public:
    template <class T>
    static Hamiltonian<T> Generate(QuantumSystem &quantumSystem)
    {
        Dimensions &dimensions = quantumSystem.dimensions;
        
        int deg = 4;
        int length = dimensions.GetLength();

        // check height for warning
        int width = dimensions.GetWidth();
        int height = dimensions.GetHeight();
        Info::DimensionsWarningOnly1D(length, width, height);

        int N = length;

        Hamiltonian<T> ham(N, deg);

        ConnectionsFiller::Spinfull(ham,quantumSystem.parametersConnections);

        return ham;
    }
};

#endif