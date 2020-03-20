#include "CountingMajorana/CountingMajorana.hpp"

int main(int argc, char *argv[])
{
	ArgvParser argvParser;
	argvParser.Parse(argc, argv);
	Dimensions dimensions = argvParser.dimensions;
	Parameters parameters = argvParser.parameters;

	VectorViewer::length = dimensions.map["Length"];
	VectorViewer::height = dimensions.map["Height"];

	/**
	 * @brief matrix typedef:
	 * support for: arma::mat, arma::sp_mat
	 */
	using matrixType = arma::sp_mat;
	/**
	 * @brief geometry and model type
	 * support for:
	 * - SpinfullUniformChain (Length)
	 * - SpinlessUniformChain (Length)
	 * - SpinfullUniform2D    (Length, Height)
	 */
	using geometry = SpinfullUniform2D;
	
	auto ham = Factory<geometry>::Generate<matrixType>(dimensions, parameters);
	//auto ham = Factory<SpinlessUniformChain>::Generate<matrixType>(L, parameters);
	//ham.Print();

	Solver::tol = 0.00; // tolerance of convergance
	Solver::noe = 30;	 // number of eigenvalues

	Solver::showVectors = true;
	Solver::Diagonalize(ham);
}
