#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Hamiltonian.hpp"
#include "SpinfullFiller.hpp"
#include "SpinlessFiller.hpp"
#include "Parameters.hpp"

Hamiltonian SpinfullUniformChain(int L, Parameters parameters)
{
    int deg = 4;
    Hamiltonian ham(L, deg);
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

Hamiltonian SpinlessUniformChain(int L, Parameters parameters)
{
    int deg = 2;
    Hamiltonian ham(L, deg);
    for (int i = 0; i < L - 1; i++)
    {
        SpinlessFiller::KineticTerm(ham, i, i + 1, parameters.map["t_integral"]);
        SpinlessFiller::ProxTerm(ham, i, i+1, parameters.map["delta"]);
    }
    for (int i = 0; i < L; i++)
    {
        SpinlessFiller::ChemicalTerm(ham, i, parameters.map["mu_potential"]);
    }

    return ham;
}

#endif