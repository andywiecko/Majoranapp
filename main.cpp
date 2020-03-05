#include <armadillo>
#include "src/Hamiltonian.hpp"
#include "src/Solver.hpp"
#include "src/ArgvParser.hpp"
#include "src/Factory.hpp"
using namespace arma;

int main(int argc, char *argv[])
{
	ArgvParser argvParser;
	argvParser.Parse(argc, argv);

	int L = argvParser.L;
	double delta = argvParser.delta;
	double t_integral = argvParser.t_integral;
	double mu_potential = argvParser.mu_potential;
	double zeeman = argvParser.zeeman;
	double rashba = argvParser.rashba;

	Hamiltonian ham = SpinfullUniformChain(L, t_integral, rashba, delta, zeeman, mu_potential);
	//Hamiltonian ham = SpinlessUniformChain(L, t_integral, delta, mu_potential);
	//ham.Print();
	Solver::Diagonalize(ham);

}
