#ifndef SPINLESSFILLER_HPP
#define SPINLESSFILLER_HPP

#include "EnumGamma.hpp"
#include "Hamiltonian.hpp"

class SpinlessFiller
{
public:
    template <class T>
    static void KineticTerm(Hamiltonian<T> &ham, int i, int j, double t_integral)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, j, -0.5 * t_integral);
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::UpMinus, i, -0.5 * t_integral);
    }

    template <class T>
    static void ProxTerm(Hamiltonian<T> &ham, int i, int j, double delta)
    {
        // TODO        
    }

    template <class T>
    static void ChemicalTerm(Hamiltonian<T> &ham, int i, double mu)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, i, -0.5 * mu);
    }
};

#endif