#ifndef SPINFULLFILLER_HPP
#define SPINFULLFILLER_HPP

#include "EnumGamma.hpp"
#include "Hamiltonian.hpp"

class SpinfullFiller
{

private:
    static void DegreeWarning()
    {
        // TODO
    }


public:
    // TODO add description (hamiltonian explicit form)
    static void KineticTerm(Hamiltonian &ham, int i, int j, double t_integral)
    {
        DegreeWarning();
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, j, -0.5 * t_integral);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownMinus, j, -0.5 * t_integral);
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::UpMinus, i, -0.5 * t_integral);
        ham.InsertBlock(Gamma::DownPlus, j, Gamma::DownMinus, i, -0.5 * t_integral);
    }

    static void RashbaTerm(Hamiltonian &ham, int i, int j, double rashba)
    {
        DegreeWarning();
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::DownMinus, j, -0.5 * rashba);
        ham.InsertBlock(Gamma::DownPlus, j, Gamma::UpMinus, i, -0.5 * rashba);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::UpMinus, j, +0.5 * rashba);
        ham.InsertBlock(Gamma::UpPlus, j, Gamma::DownMinus, i, +0.5 * rashba);
    }

    static void ProxTerm(Hamiltonian &ham, int i, double delta)
    {
        DegreeWarning();
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::DownMinus, i, +0.5 * delta);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::UpMinus, i, -0.5 * delta);
    }

    static void ZeemanTerm(Hamiltonian &ham, int i, double zeeman)
    {
        DegreeWarning();
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, i, -0.5 * zeeman);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownMinus, i, +0.5 * zeeman);
    }

    static void ChemicalTerm(Hamiltonian &ham, int i, double mu)
    {
        DegreeWarning();
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, i, -0.5 * mu);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownMinus, i, -0.5 * mu);
    }
};

#endif