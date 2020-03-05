#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Hamiltonian.hpp"
#include "SpinfullFiller.hpp"
#include "SpinlessFiller.hpp"

Hamiltonian SpinfullUniformChain(int L, double t_integral, double rashba, double delta, double zeeman, double mu)
{
    int deg = 4;
    Hamiltonian ham(L, deg);
    for (int i = 0; i < L - 1; i++)
    {
        SpinfullFiller::KineticTerm(ham, i, i + 1, t_integral);
        SpinfullFiller::RashbaTerm(ham, i, i + 1, rashba);
    }
    for (int i = 0; i < L; i++)
    {
        SpinfullFiller::ProxTerm(ham, i, delta);
        SpinfullFiller::ZeemanTerm(ham, i, zeeman);
        SpinfullFiller::ChemicalTerm(ham, i, mu);
    }

    return ham;
}

Hamiltonian SpinlessUniformChain(int L, double t_integral, double delta, double mu)
{
    int deg = 2;
    Hamiltonian ham(L, deg);
    for (int i = 0; i < L - 1; i++)
    {
        SpinlessFiller::KineticTerm(ham, i, i + 1, t_integral);
        SpinlessFiller::ProxTerm(ham, i, i+1, delta);
    }
    for (int i = 0; i < L; i++)
    {
        SpinlessFiller::ChemicalTerm(ham, i, mu);
    }

    return ham;
}

#endif