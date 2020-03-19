#ifndef FACTORY_SPINFULLUNIFORMCHAIN_HPP
#define FACTORY_SPINFULLUNIFORMCHAIN_HPP

#include "../Hamiltonian.hpp"
#include "../Parameters.hpp"
#include "../SpinfullFiller.hpp"

class SpinfullUniformChain
{
public:
    template <class T>
    static Hamiltonian<T> Generate(int &L, Parameters &parameters)
    {
        int deg = 4;
        Hamiltonian<T> ham(L, deg);
        for (int i = 0; i < L - 1; i++)
        {
            SpinfullFiller::KineticTerm(ham, i, i + 1, parameters.map["t_integral"]);
            SpinfullFiller::RashbaTerm(ham, i, i + 1, parameters.map["rashba"]);
        }
        for (int i = 0; i < L; i++)
        {
            SpinfullFiller::ProxTerm(ham, i, parameters.map["delta"]);
            SpinfullFiller::ZeemanTerm(ham, i, parameters.map["zeeman"]);
            SpinfullFiller::ChemicalTerm(ham, i, parameters.map["mu_potential"]);
        }

        return ham;
    }
};

#endif