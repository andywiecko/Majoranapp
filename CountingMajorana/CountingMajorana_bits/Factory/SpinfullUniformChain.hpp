#ifndef FACTORY_SPINFULLUNIFORMCHAIN_HPP
#define FACTORY_SPINFULLUNIFORMCHAIN_HPP

#include <map>
#include "../Hamiltonian.hpp"
#include "../Parameters.hpp"
#include "../Dimensions.hpp"
#include "../SpinfullFiller.hpp"

class SpinfullUniformChain
{
public:
    template <class T>
    static Hamiltonian<T> Generate(Dimensions &dimensions, Parameters &parameters)
    {
        int deg = 4;
        int L = dimensions.map["Length"];
        Hamiltonian<T> ham(L, deg);
        auto & map = parameters.map;
        for (int i = 0; i < L - 1; i++)
        {
            SpinfullFiller::KineticTerm(ham, i, i + 1, map[SpinfullFiller::KineticTermName]);
            SpinfullFiller::RashbaTerm(ham, i, i + 1,
                                       map[SpinfullFiller::RashbaTermXName],
                                       map[SpinfullFiller::RashbaTermYName]);
        }
        for (int i = 0; i < L; i++)
        {
            SpinfullFiller::ProxTerm(ham, i, map[SpinfullFiller::ProxTermName]);
            SpinfullFiller::ZeemanTerm(ham, i, map[SpinfullFiller::ZeemanTermName]);
            SpinfullFiller::ChemicalTerm(ham, i, map[SpinfullFiller::ChemicalTermName]);
        }

        return ham;
    }
};

#endif