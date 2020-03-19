#ifndef FACTORY_SPINLESSUNIFORMCHAIN_HPP
#define FACTORY_SPINLESSUNIFORMCHAIN_HPP

#include "../Hamiltonian.hpp"
#include "../Parameters.hpp"
#include "../SpinlessFiller.hpp"

class SpinlessUniformChain
{
public:
    template <class T>
    static Hamiltonian<T> Generate(int &L, Parameters &parameters)
    {
        int deg = 2;
        Hamiltonian<T> ham(L, deg);
        for (int i = 0; i < L - 1; i++)
        {
            SpinlessFiller::KineticTerm(ham, i, i + 1, parameters.map["t_integral"]);
            SpinlessFiller::ProxTerm(ham, i, i + 1, parameters.map["delta"]);
        }
        for (int i = 0; i < L; i++)
        {
            SpinlessFiller::ChemicalTerm(ham, i, parameters.map["mu_potential"]);
        }

        return ham;
    }
};

#endif