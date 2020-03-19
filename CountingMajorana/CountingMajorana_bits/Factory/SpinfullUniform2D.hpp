#ifndef FACTORY_SPINFULLUNIFORM2D_HPP
#define FACTORY_SPINFULLUNIFORM2D_HPP

#include "../Hamiltonian.hpp"
#include "../Parameters.hpp"
#include "../Dimensions.hpp"
#include "../SpinfullFiller.hpp"

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
            SpinfullFiller::ProxTerm(ham, i, parameters.map["delta"]);
            SpinfullFiller::ZeemanTerm(ham, i, parameters.map["zeeman"]);
            SpinfullFiller::ChemicalTerm(ham, i, parameters.map["mu_potential"]);
        }

        for (int x = 0; x < length - 1; x++)
        {
            for (int y = 0; y < height - 1; y++)
            {
                SpinfullFiller::KineticTerm(ham, x, y, parameters.map["t_integral"]);
                SpinfullFiller::RashbaTerm(ham, x, y,
                                           parameters.map["rashbaX"],
                                           parameters.map["rashbaY"]);
            }
        }

        return ham;
    }
};

#endif