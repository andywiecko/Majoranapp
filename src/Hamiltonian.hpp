#ifndef HAMILTONIAN_HPP
#define HAMILTONIAN_HPP

#include <armadillo>
#include "EnumGamma.hpp"

template <class T>
class Hamiltonian
{
private:
   int deg;

public:
   int L;
   T elements;
   Hamiltonian(int _L, int _deg)
   {
      L = _L;
      deg = _deg;
      elements.set_size(deg * L, deg * L);
      elements.fill(0);
   }

   void InsertBlock(Gamma gammai, int i, Gamma gammaj, int j, double value)
   {
      int ishift = static_cast<int>(gammai) % deg;
      int jshift = static_cast<int>(gammaj) % deg;
      this->elements(deg * i + ishift, deg * j + jshift) += value;
   }

   void Print()
   {
      this->elements.print();
   }
};

#endif
