#include "CountingMajorana/CountingMajorana.hpp"

int main(int argc, char *argv[])
{
	ArgvParser argvParser;
	argvParser.Parse(argc, argv);
	int L = argvParser.L;
	Parameters parameters = argvParser.parameters;

	/**
	 * @brief matrix typedef:
	 * support for: arma::mat, arma::sp_mat
	 */
	using matrixType = arma::sp_mat;

	auto ham = SpinfullUniformChain<matrixType>(L, parameters);
	//auto ham = SpinlessUniformChain<matrixType>(L, parameters);
	
	//ham.Print();

	Solver::tol = 0.001; // tolerance of convergance
	Solver::noe = 25; // number of eigenvalues 
	Solver::Diagonalize(ham);

}
