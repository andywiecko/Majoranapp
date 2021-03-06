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
     * @brief number of eigenvectors
     */
    static size_t nov;
    /**
     * @brief target part of the spectrum
     */
    static std::string target;

    /**
     * @brief show eigenvalues (flag)
     */
    static bool showEigenvalues;

    /**
     * @brief show eigenvectors (flag)
     */
    static bool showEigenvectors;

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
        Info::LogBegining("Solving eigen-equation...");
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

        Info::LogAccomplished();

        if (showEigenvalues)
            eigval.print("# === λ ===");
        if (showEigenvectors)
        {
            //arma::mat vectors = join_horiz(eigvec.col(0),eigvec.col(1));
            arma::mat vectors = eigvec.cols(0, nov < size ? nov - 1 : size - 1);
            VectorViewer::View(vectors, ham.deg);
        }
    }
};

double Solver::tol = 0.0;
size_t Solver::noe = 10;
size_t Solver::nov = 2;
std::string Solver::target = "sa";
bool Solver::showEigenvalues = true;
bool Solver::showEigenvectors = false;

#endif
