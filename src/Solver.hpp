#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "SpinfullHamiltonian.hpp"

class Solver
{
public:
    static void Diagonalize(SpinfullHamiltonian &ham)
    {
        int L = ham.L;
        mat M = ham.elements;
        mat ATA = -(M - M.t()) * (M - M.t());

        vec eigval;
        mat eigvec;
        eig_sym(eigval, eigvec, ATA);

        vec MO(4 * L);
        vec OM(4 * L);
        for (int i = 0; i < 4 * L; i++)
        {
            vec O = eigvec.col(i);
            MO(i) = as_scalar(O.t() * M.t() * M * O);
            OM(i) = as_scalar(O.t() * M * M.t() * O);
        }
        //join_horiz(eigval, MO, OM).print("#eig         |MO|     |OTM|");
        eigval.print("#eig");
        mat O = eigvec;
        //join_horiz(O.col(0), O.col(1)).print("\n#vec");
    }
};

#endif
