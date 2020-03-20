#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <string>
#include "Hamiltonian.hpp"
#include "VectorViewer.hpp"

/**
 * @brief static solver
 */
class Solver
{
public:
    //solver options

    /**
     * @brief tolerance for arma::eigs_sym procedure
     */
    static double tol;
    /**
     * @brief number of eigenvalues
     */
    static size_t noe;
    /**
     * @brief target part of the spectrum
     */
    static std::string target;

    /**
     * @brief procedure for solving:
     * -(M-M^T).(M-M^T)
     * 
     * @tparam T support for: arma::mat, arma::sp_mat
     * @param ham 
     */
    template <class T>
    static void Diagonalize(Hamiltonian<T> &ham)
    {
        size_t size = ham.elements.n_cols;
        T &M = ham.elements;
        T ATA = -(M - M.t()) * (M - M.t());

        arma::vec eigval;
        arma::mat eigvec;

        if constexpr (std::is_same<T, arma::mat>::value)
            arma::eig_sym(eigval, eigvec, ATA);

        if constexpr (std::is_same<T, arma::sp_mat>::value)
        {
            int k = (size < noe) ? size - 1 : noe;
            arma::eigs_sym(eigval, eigvec, ATA, k, target.c_str(), tol);
        }

        //eigval.print("# == eigs ==");
        //arma::mat vectors = join_horiz(eigvec.col(0),eigvec.col(1));
        //VectorViewer::View2DGrid<arma::mat>(vectors, ham.deg,100,10);
    }
};

double Solver::tol = 0.0;
size_t Solver::noe = 10;
std::string Solver::target = "sa";

#endif
