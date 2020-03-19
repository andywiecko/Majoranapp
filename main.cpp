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
	/**
	 * @brief geometry and model type
	 * support for:
	 * - SpinfullUniformChain
	 * - SpinlessUniformChain
	 */
	using geometry = SpinfullUniformChain;

	auto ham = Factory<geometry>::Generate<matrixType>(L, parameters);
	//auto ham = Factory<SpinlessUniformChain>::Generate<matrixType>(L, parameters);
	//ham.Print();

	Solver::tol = 0.005; // tolerance of convergance
	Solver::noe = 30;	 // number of eigenvalues
	Solver::Diagonalize(ham);
}
