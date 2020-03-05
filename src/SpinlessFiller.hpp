#ifndef SPINLESSFILLER_HPP
#define SPINLESSFILLER_HPP

#include "EnumGamma.hpp"
#include "Hamiltonian.hpp"

class SpinlessFiller
{
public:
    static void KineticTerm(Hamiltonian &ham, int i, int j, double t_integral)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, j, -0.5 * t_integral);
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::UpMinus, i, -0.5 * t_integral);
    }

    static void ProxTerm(Hamiltonian &ham, int i, int j, double delta)
    {
        // TODO        
    }

    static void ChemicalTerm(Hamiltonian &ham, int i, double mu)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, i, -0.5 * mu);
    }
};

#endif