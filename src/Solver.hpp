#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Hamiltonian.hpp"

class Solver
{
public:
    template <class T>
    static void Diagonalize(Hamiltonian<T> &ham)
    {
        //int L = ham.L;
        arma::mat M = ham.elements;
        size_t size = M.n_cols;
        arma::mat ATA = -(M - M.t()) * (M - M.t());

        arma::vec eigval;
        arma::mat eigvec;
        arma::eig_sym(eigval, eigvec, ATA);

        arma::vec MO(size);
        arma::vec OM(size);
        for (size_t i = 0; i < size; i++)
        {
            arma::vec O = eigvec.col(i);
            MO(i) = as_scalar(O.t() * M.t() * M * O);
            OM(i) = as_scalar(O.t() * M * M.t() * O);
        }
        //join_horiz(eigval, MO, OM).print("#eig         |MO|     |OTM|");
        eigval.print("# === eigs ===");
        arma::mat O = eigvec;
        //join_horiz(O.col(0), O.col(1)).print("\n#vec");
    }
};

#endif
