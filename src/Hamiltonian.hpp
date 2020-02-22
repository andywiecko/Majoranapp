#ifndef HAMILTONIAN_HPP
#define HAMILTONIAN_HPP

#include <armadillo>
using namespace arma;

class Hamiltonian
{
private:
   int L;
   mat elements;

public:
   Hamiltonian(int _L)
   {
      L = _L;
      elements.set_size(2 * L, 2 * L);
      elements.fill(0);
   }

   void InsertBlock(int i, int j, double delta, double t_integral, double phi)
   {
      this->elements(2 * i, 2 * j) = -delta * std::sin(phi);
      this->elements(2 * i + 1, 2 * j) = delta * std::cos(phi) + t_integral;
      this->elements(2 * i, 2 * j + 1) = delta * std::cos(phi) - t_integral;
      this->elements(2 * i + 1, 2 * j + 1) = delta * std::sin(phi);
   }

   void InsertSite(int i, double mu_potential)
   {
      this->elements(2 * i, 2 * i + 1) += mu_potential;
   }

   void Print()
   {
      this->elements.print();
   }

   void Diagonalize()
   {
      mat M = this->elements;
      mat ATA = -(M - M.t()) * (M - M.t());

      vec eigval;
      mat eigvec;
      eig_sym(eigval, eigvec, ATA);

      vec MO(2 * this->L);
      vec OM(2 * this->L);
      for (int i = 0; i < 2 * this->L; i++)
      {
         vec O = eigvec.col(i);
         MO(i) = as_scalar(O.t() * M.t() * M * O);
         OM(i) = as_scalar(O.t() * M * M.t() * O);
      }

      //join_horiz(eigval, MO, OM).print("#eig         |MO|     |OTM|");
      eigval.print("#eig");

      mat O = eigvec;
      join_horiz(O.col(0), O.col(1)).print("\n#vec");
   }

   void LoadBlocks(mat ind, vec deltas, vec t_integrals, vec phis)
   {
      //
      for (int i = 0; i < ind.n_rows; i++)
      {
         mat row = ind.row(i);
         int ii = row(0);
         int jj = row(1);
         this->InsertBlock(ii, jj, deltas(i), t_integrals(i), phis(i));
      }
   }
};

Hamiltonian LoadFromFile(std::string filename)
{
   mat A;
   A.load(filename, arma_ascii);
   mat ind = A.cols(0, 1);
   int L = ind.max() + 1;
   Hamiltonian Ham(L);

   vec deltas = A.col(2);
   vec t_integrals = A.col(3);
   vec phis = A.col(4);

   Ham.LoadBlocks(ind, deltas, t_integrals, phis);
   return Ham;
}

Hamiltonian UniformChain(int L, double delta, double t_integral, double mu_potential = 0)
{
   Hamiltonian Ham(L);
   for (int i = 0; i < L - 1; i++)
      Ham.InsertBlock(i, i + 1, delta, t_integral, 0.0);
   for (int i = 0; i < L; i++)
      Ham.InsertSite(i, mu_potential);
   return Ham;
}

#endif