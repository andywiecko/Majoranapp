#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Hamiltonian.hpp"

class Solver
{
public:
    static void Diagonalize(Hamiltonian &ham)
    {
        //int L = ham.L;
        mat M = ham.elements;
        size_t size = M.n_cols;
        mat ATA = -(M - M.t()) * (M - M.t());

        vec eigval;
        mat eigvec;
        eig_sym(eigval, eigvec, ATA);

        vec MO(size);
        vec OM(size);
        for (size_t i = 0; i < size; i++)
        {
            vec O = eigvec.col(i);
            MO(i) = as_scalar(O.t() * M.t() * M * O);
            OM(i) = as_scalar(O.t() * M * M.t() * O);
        }
        //join_horiz(eigval, MO, OM).print("#eig         |MO|     |OTM|");
        eigval.print("# === eigs ===");
        mat O = eigvec;
        //join_horiz(O.col(0), O.col(1)).print("\n#vec");
    }
};

#endif
