#include "CountingMajorana/CountingMajorana.hpp"

int main(int argc, char *argv[])
{
	ArgvParser argvParser;
	if (argvParser.Parse(argc, argv))
		return 0;

	Dimensions dimensions = argvParser.dimensions;
	Parameters parameters = argvParser.parameters;

	if (ModelSelector::GetSelected() == " @ ")
	{
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
	 	 * - SpinfullUniform2D    (Length, Width)
	 	 */
		using geometry = SpinfullUniform2D;

		auto ham = Factory<geometry>::Generate<matrixType>(dimensions, parameters);

		Solver::tol = 0.005; // tolerance of convergance
		Solver::noe = 30;	 // number of eigenvalues
		Solver::showEigenvectors = true;
		Solver::Diagonalize(ham);
	}
	// parsed from JSON
	else if (ModelSelector::SparseSelected())
	{
		auto ham = ModelSelector::SelectSparse(dimensions, parameters);
		Solver::Diagonalize(ham);
	}
	else if (ModelSelector::DenseSelected())
	{
		auto ham = ModelSelector::SelectDense(dimensions, parameters);
		Solver::Diagonalize(ham);
	}
	else
	{
		Info::Warning("Warning, unrecognized model and/or matrix type: ",
					  ModelSelector::GetSelected());
		Info::Warning("Exiting...");
	}
}
