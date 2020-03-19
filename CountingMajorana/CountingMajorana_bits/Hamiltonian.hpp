#ifndef HAMILTONIAN_HPP
#define HAMILTONIAN_HPP

#include <armadillo>
#include "EnumGamma.hpp"

/**
 * @brief Hamiltonian class for counting MZM in non-interacting systems
 * 
 * @tparam T matrix type, support for: arma::mat, arma::sp_mat
 */
template <class T>
class Hamiltonian
{
private:
   /**
    * @brief number degree of freedom
    * deg = 2 spinless systems
    * deg = 4 spinfull systems (1/2 spin)
    */
   int deg;

public:
   /**
    * @brief number of sites
    */
   int N;
   /**
    * @brief matrix element container
    */
   T elements;
   /**
    * @brief Construct a new Hamiltonian object
    * 
    * @param _N number of sites
    * @param _deg degree of freedom
    */
   Hamiltonian(int _N, int _deg) : deg{_deg}, N{_N}
   {
      elements.set_size(deg * N, deg * N);

      // [!] only for arma::mat
      if constexpr (std::is_same<T, arma::mat>::value)
         elements.fill(0);
   }

   /**
    * @brief insert block: value * gamma_i^alpha gamma_j^beta
    * 
    * @param gammai type of gamma
    * @param i site index
    * @param gammaj type of gamma
    * @param j site index
    * @param value 
    */
   void InsertBlock(Gamma gammai, int i, Gamma gammaj, int j, double value)
   {
      int ishift = static_cast<int>(gammai) % deg;
      int jshift = static_cast<int>(gammaj) % deg;
      this->elements(deg * i + ishift, deg * j + jshift) += value;
   }

   /**
    * @brief display matrix elements
    */
   void Print()
   {
      this->elements.print();
   }
};

#endif
