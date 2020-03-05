#include <armadillo>
#include "src/Hamiltonian.hpp"
#include "src/Solver.hpp"
#include "src/ArgvParser.hpp"
#include "src/Factory.hpp"
#include "src/Parameters.hpp"
using namespace arma;

int main(int argc, char *argv[])
{
	ArgvParser argvParser;
	argvParser.Parse(argc, argv);
	int L = argvParser.L;
	Parameters parameters = argvParser.parameters;

	Hamiltonian ham = SpinfullUniformChain(L, parameters);
	//Hamiltonian ham = SpinlessUniformChain(L, parameters);
	//ham.Print();
	Solver::Diagonalize(ham);

}
