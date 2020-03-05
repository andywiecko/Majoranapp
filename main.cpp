#include <armadillo>
#include "src/Hamiltonian.hpp"
#include "src/SpinfullHamiltonian.hpp"
#include "src/Solver.hpp"
#include "src/ArgvParser.hpp"
using namespace arma;

int main(int argc, char *argv[])
{

	ArgvParser argvParser;
	argvParser.Parse(argc,argv);

	//Hamiltonian Ham = LoadFromFile("ham.txt");

	int    L =            argvParser.L;
	double delta =        argvParser.delta;
	double t_integral =   argvParser.t_integral;
	double mu_potential = argvParser.mu_potential;
	double zeeman =       argvParser.zeeman;
	double rashba =       argvParser.rashba;

	SpinfullHamiltonian ham = UniformChain(L, t_integral, rashba,delta,zeeman,mu_potential);
	//ham.Print();
	Solver::Diagonalize(ham);

	//Hamiltonian ham = UniformChain(L, delta, t_integral, mu_potential);
	//Solver::Diagonalize(ham);
	//Ham.Diagonalize();
	//Ham.Print();

	
}
