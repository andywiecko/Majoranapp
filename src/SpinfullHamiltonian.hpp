#ifndef SPINFULLHAMILTONIAN_HPP
#define SPINFULLHAMILTONIAN_HPP

#include <armadillo>
using namespace arma;

enum class Gamma 
{
    UpPlus = 0,
    UpMinus = 1,
    DownPlus = 2,
    DownMinus = 3
};

class SpinfullHamiltonian
{

private:
   int deg = 4;

public:
   int L;
   mat elements;
   SpinfullHamiltonian(int _L, int _deg = 4)
   {
      L = _L;
      elements.set_size(deg * L, deg * L);
      elements.fill(0);
   }

   void InsertBlock(Gamma gammai, int i, Gamma gammaj, int j, double value)
   {
      int ishift = static_cast<int>(gammai);
      int jshift = static_cast<int>(gammaj);
      this->elements(deg * i+ishift,deg * j+jshift) += value;
   }

   void Print()
   {
      this->elements.print();
   }
  
   void KineticTerm(int i, int j, double t_integral)
   {
      this->InsertBlock(Gamma::UpPlus,i,Gamma::UpMinus,j,-0.5 * t_integral);
      this->InsertBlock(Gamma::DownPlus,i,Gamma::DownMinus,j,-0.5 * t_integral);
      this->InsertBlock(Gamma::UpPlus,j,Gamma::UpMinus,i,-0.5 * t_integral);
      this->InsertBlock(Gamma::DownPlus,j,Gamma::DownMinus,i,-0.5 * t_integral);
   }

   void RashbaTerm(int i, int j, double rashba)
   {
      this->InsertBlock(Gamma::UpPlus,i,Gamma::DownMinus,j,-0.5 * rashba);
      this->InsertBlock(Gamma::DownPlus,j,Gamma::UpMinus,i,-0.5 * rashba);
      this->InsertBlock(Gamma::DownPlus,i,Gamma::UpMinus,j,+0.5 * rashba);
      this->InsertBlock(Gamma::UpPlus,j,Gamma::DownMinus,i,+0.5 * rashba);
   }

   void ProxTerm(int i,double delta)
   {
      this->InsertBlock(Gamma::UpPlus,i,Gamma::DownMinus,i,+0.5 * delta);
      this->InsertBlock(Gamma::DownPlus,i,Gamma::UpMinus,i,-0.5 * delta);
   }

   void ZeemanTerm(int i, double zeeman)
   {
      this->InsertBlock(Gamma::UpPlus,i,Gamma::UpMinus,i,-0.5 * zeeman);
      this->InsertBlock(Gamma::DownPlus,i,Gamma::DownMinus,i,+0.5 * zeeman);
   }

   void ChemicalTerm(int i, double mu)
   {
      this->InsertBlock(Gamma::UpPlus,i,Gamma::UpMinus,i,-0.5 * mu);
      this->InsertBlock(Gamma::DownPlus,i,Gamma::DownMinus,i,-0.5 * mu);
   }



};

SpinfullHamiltonian UniformChain(int L,double t_integral, double rashba,double delta, double zeeman, double mu)
{
   SpinfullHamiltonian ham(L);
   for( int i=0;i<L-1;i++)
   {
	   ham.KineticTerm(i,i+1,t_integral);
	   ham.RashbaTerm(i,i+1,rashba);
   }
   for (int i=0;i<L;i++)
   {
	   ham.ProxTerm(i,delta);
	   ham.ZeemanTerm(i,zeeman);
	   ham.ChemicalTerm(i,mu);
   }


   return ham;

}


#endif
