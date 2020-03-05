#include <armadillo>
#include "src/Hamiltonian.hpp"
#include "src/Solver.hpp"
#include "src/ArgvParser.hpp"
#include "src/Factory.hpp"
#include "src/Parameters.hpp"

int main(int argc, char *argv[])
{
	ArgvParser argvParser;
	argvParser.Parse(argc, argv);
	int L = argvParser.L;
	Parameters parameters = argvParser.parameters;

	using matrixType = arma::sp_mat;
	Hamiltonian<matrixType> ham = SpinfullUniformChain<matrixType>(L, parameters);
	//Hamiltonian ham = SpinlessUniformChain(L, parameters);
	//ham.Print();
	//Solver::Diagonalize(ham);

}
