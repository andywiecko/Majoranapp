#include <armadillo>
#include "src/Hamiltonian.hpp"
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

	Hamiltonian Ham = UniformChain(L, delta, t_integral, mu_potential);

	Ham.Diagonalize();
	//Ham.Print();

	return 0;
}
