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
   int L;
   /**
    * @brief matrix element container
    */
   T elements;
   Hamiltonian(int _L, int _deg)
   {
      L = _L;
      deg = _deg;
      elements.set_size(deg * L, deg * L);

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
